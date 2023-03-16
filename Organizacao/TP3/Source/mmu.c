#include "mmu.h"
#include <stdio.h>
#include <math.h>

bool canOnlyReplaceBlock(Line line) {
    // Or the block is empty or
    // the block is equal to the one in memory RAM and can be replaced
    if (line.tag == INVALID_ADD || (line.tag != INVALID_ADD && !line.updated))
        return true;
    return false;
}


#ifdef MAPEAMENTO_ASSOCIATIVO_POR_CONJUNTO
    int mapeamentoAssociativoPorConjunto(int address, Cache* cache){

        if(cache->size < 12)
            return -1;

        const int DIVISOR = 4;

        int divisoes = cache->size / DIVISOR;
        int resto = cache->size % DIVISOR; 

        int posicaoProcura = 0;

        //procurando a tag com o endereco desejado
        //Fazendo a procura em quatro particoes ao mesmo tempo
        for(int i = 0; i < divisoes; i++){
            
            for(int j = 0; j < DIVISOR; j++){
                
                posicaoProcura = i + j * divisoes;

                if(address == cache->lines[posicaoProcura].tag){
                    return posicaoProcura;
                }
                
            }
        }

        //Procurando no resto
        for(int i = cache->size - resto; i < cache->size; i++){

            if(address == cache->lines[posicaoProcura].tag){
                return i;
            }
        }

        //Retorno 0 como padrão para caso nao encontre
        return 0;

    }
#endif

int memoryCacheMapping(int address, Cache* cache) {   
    #ifdef MAPEAMENTO_DIRETO
        return address % cache->size;
    #endif

    #if defined MAPEAMENTO_ASSOCIATIVO || defined MAPEAMENTO_ASSOCIATIVO_POR_CONJUNTO
        
        #ifdef MAPEAMENTO_ASSOCIATIVO_POR_CONJUNTO
            //Faz a procura por conjunto, dividindo o numero por algum valor. Caso o tamanho da cache seja primo, faz o associativo normal
            int posicao = mapeamentoAssociativoPorConjunto(address, cache);
            if(posicao != -1)
                return posicao;
        #endif

        for(int i=0; i<cache->size; i++){
            //Varre a cache, procurando a tag que contem o endereco desejado
            if(address == cache->lines[i].tag){
                return i;
            }
        }
        return 0;
    
    #endif
}

int memoryRAMMapping(int address, RAM *ram){
    #ifdef MAPEAMENTO_ASSOCIATIVO
        for(int i = 0; i < ram->size; i++){
            if(address == ram->blocks[i].enderecoEmDisco){ //caso o endereco passado seja igual a tag do bloco da ram, retorna a posicao no vetor de memoryblocks
                return i;
            }
        }

        return 0;
    #endif
}

int blockFromRAMWillBeRemoved(RAM *ram){
    #ifdef LFU
        MemoryBlock menor = ram->blocks[0];
        int pos = 0;

        for(int i = 0; i < ram->size;i++){
            if(menor.count > ram->blocks[i].count){
                menor = ram->blocks[i];
                pos = i;
            }
        }

        return pos;
    #endif

    #ifdef RANDOM
        return rand() % ram->size;
    #endif
}

//Varre o vetor de linhas da cache 
int procurarBlocoASair(Cache* cache){

    #ifdef MAPEAMENTO_DIRETO
        return address % cache->size;
    #endif

    int posicao = 0;

    //Verificando se há posições vazias na cache. Caso tenha, retorna a posição vazia
    #ifndef RANDOM
        for(int i = 0; i < cache->size; i++){
            if(cache->lines[i].tag == -1)
                return i;
        }
    #endif

    //Procura a linha com o menor numero de utilizacoes - LFU
    #ifdef LFU
        
        Line menosUsada = cache->lines[0];
        for(int i = 1; i < cache->size; i++){
            if(cache->lines[i].contador < menosUsada.contador){
                menosUsada = cache->lines[i];
                posicao = i;
            }
        }
        
    #endif

    //Procura a linha com o maior numero de utilizacoes - LRU
    //Procura a linha com o maior tempo na cache - FIFO
    #if defined LRU || defined FIFO
    
        Line maisUsado = cache->lines[0];
        for(int i = 1; i < cache->size; i++){
            if(cache->lines[i].contador > maisUsado.contador){
                maisUsado = cache->lines[i];
                posicao = i;
            }
        }

    #endif

    //Gera uma posicao aleatoria da cache para ser removida
    #ifdef RANDOM
        posicao = rand() % (cache->size);
    #endif

    return posicao;
}

#if defined LFU || defined LRU || defined FIFO
    void reiniciaContador(Cache* cache, int posLinha){
        cache->lines[posLinha].contador = 0;
    }
#endif

#if defined LRU || defined FIFO 
    void adicionarMaisUmNoContador(Cache * cache, int posUsado){
        //Incrementando mais um em todas os contadores das linhas
        for(int i = 0; i < cache->size; i++){
            if(cache->lines[i].tag != INVALID_ADD)
            cache->lines[i].contador++;
        }
        
        #ifdef LRU
            //Colocando a linha atual como zero
            cache->lines[posUsado].contador = 0;
        #endif
    }
#endif

void updateMachineInfos(Machine* machine, int hitMiss, int cost) {
    switch (hitMiss) {
        case 1:
            machine->hitL1 += 1;
            break;

        case 2:
            machine->hitL2 += 1;
            machine->missL1 += 1;
            break;

        case 3:
            machine->missL1 += 1;
            machine->missL2 += 1;
            machine->hitL3 += 1;
            break;
        
        case 4:
            machine->hitRAM += 1;
            machine->missL1 += 1;
            machine->missL2 += 1;
            machine->missL3 += 1;
            break;

        case 5:
            machine->missL1 += 1;
            machine->missL2 += 1;
            machine->missL3 += 1;
            machine->missRAM += 1;
            machine->hitDisk += 1;
            break;
    }
    machine->totalCost += cost;
}

void atualizaDisco(MemoryBlock *ram){
    FILE *arquivo = fopen("disk.dat", "rb");
    MemoryBlock disco[DISK_SIZE];
    for (int i = 0; i < DISK_SIZE; i++)
    {
        int id;
        int v[WORDS_SIZE];
        fread(&id, sizeof(int), 1, arquivo);
        fread(v, sizeof(int), WORDS_SIZE, arquivo);
        disco[i].enderecoEmDisco = id;

        for (int j = 0; j < WORDS_SIZE; j++)
            disco[i].words[j] = v[j];
    
    }

    fclose(arquivo);

    arquivo = fopen("diskTemp.dat", "wb");
    //grava todos os registros anteriores ao que sera alterado
    for(int i = 0; i < ram->enderecoEmDisco; i++){
        fwrite(&disco[i].enderecoEmDisco, sizeof(int), 1, arquivo);
        fwrite(disco[i].words, sizeof(int), WORDS_SIZE, arquivo);
    }

    //grava o novo registro
    fwrite(&ram->enderecoEmDisco, sizeof(int), 1, arquivo);
    fwrite(ram->words, sizeof(int), WORDS_SIZE, arquivo);

    //grava os demais registros
    for (int i = ram->enderecoEmDisco + 1; i < DISK_SIZE; i++){
        fwrite(&disco[i].enderecoEmDisco, sizeof(int), 1, arquivo);
        fwrite(disco[i].words, sizeof(int), WORDS_SIZE, arquivo);
    }

    rename("diskTemp.dat", "disk.dat");

    fclose(arquivo);
}

Line* MMUSearchOnMemorys(Address add, Machine* machine) {
    // Strategy => write back
    
    // Mapeamento da memoria
    int l1pos = memoryCacheMapping(add.block, &machine->l1);
    int l2pos = memoryCacheMapping(add.block, &machine->l2);
    int l3pos = memoryCacheMapping(add.block, &machine->l3);
    int rampos = memoryRAMMapping(add.block, &machine->ram);
    
    MemoryBlock* RAM = machine->ram.blocks;
    Line* cache1 = machine->l1.lines;
    Line* cache2 = machine->l2.lines;
    Line* cache3 = machine->l3.lines;

    //Adiciona mais um no tempo de vida de todos os valores da cache
    #ifdef FIFO
        adicionarMaisUmNoContador(&machine->l1, l1pos);
        adicionarMaisUmNoContador(&machine->l2, l2pos);
        adicionarMaisUmNoContador(&machine->l3, l3pos);
    #endif

    if (cache1[l1pos].tag == add.block) { 
        /* Block is in memory cache L1 */
        cache1[l1pos].cost = COST_ACCESS_L1;
        cache1[l1pos].cacheHit = 1;
        
        #ifdef LFU
            cache1[l1pos].contador += 1;
        #endif

        #ifdef LRU
            adicionarMaisUmNoContador(&machine->l1, l1pos);
        #endif
    } 
    else if (cache2[l2pos].tag == add.block) { 
        /* Block is in memory cache L2 */
        cache2[l2pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2;
        cache2[l2pos].cacheHit = 2;
        
        #ifdef LFU
            cache2[l2pos].contador += 1;
        #endif

        #ifdef LRU
            adicionarMaisUmNoContador(&machine->l2, l2pos);
        #endif

        updateMachineInfos(machine, cache2[l2pos].cacheHit, cache2[l2pos].cost);

        #ifdef CAN_BE_IMPROVED

            //Levando da cache 2 para a cache 1
            int posL1 = procurarBlocoASair(&machine->l1);
            Line leaveL1 = cache1[posL1];

            cache1[posL1] = cache2[l2pos];
            cache2[l2pos] = leaveL1;        

            #ifndef RANDOM 
                reiniciaContador(&machine->l2, l2pos);
                reiniciaContador(&machine->l1, l1pos);
            #endif

            return &(cache1[l1pos]); 

        #endif
        
        #ifndef CAN_BE_IMPROVED

            return &(cache2[l2pos]); 

        #endif
    } 
    else if(cache3[l3pos].tag == add.block){

        cache3[l3pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3;
        cache3[l3pos].cacheHit = 3; 
        
        #ifdef LFU
            cache3[l3pos].contador += 1;
        #endif

        #ifdef LRU
            adicionarMaisUmNoContador(&machine->l3, l3pos);
        #endif

        updateMachineInfos(machine, cache3[l3pos].cacheHit, cache3[l3pos].cost);
        return &(cache3[l3pos]);
    } 
    else if(RAM[rampos].enderecoEmDisco == add.block){
                
        atualizaDisco(&(RAM[rampos]));

        l3pos = procurarBlocoASair(&machine->l3);
        
        for (int i = 0; i < WORDS_SIZE; i++) //passa as palavras para a l3
            cache3[l3pos].block.words[i] = RAM[rampos].words[i];
        
        cache3[l3pos].tag = RAM[rampos].enderecoEmDisco;
        
        #ifdef LFU
            cache3[l3pos].contador += 1;
            RAM[rampos].count +=1;
        #endif

        cache3[l3pos].cacheHit = 4;
        cache3[l3pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM;
        updateMachineInfos(machine, cache3[l3pos].cacheHit, cache3[l3pos].cost);
        return &(cache3[l3pos]);
        
    }
    else { 
        
        //Procurando os blocos que podem sair de cada linha
        l1pos = procurarBlocoASair(&machine->l1);
        l2pos = procurarBlocoASair(&machine->l2);
        l3pos = procurarBlocoASair(&machine->l3);
        rampos = blockFromRAMWillBeRemoved(&machine->ram);
        
        
        if (!canOnlyReplaceBlock(cache1[l1pos])) { 
            /* The block on cache L1 cannot only be replaced, the memories must be updated */
            if (!canOnlyReplaceBlock(cache2[l2pos])) {
                
                if (!canOnlyReplaceBlock(cache3[l3pos])) {
                    //passa da RAM para o disco
                    atualizaDisco(&(RAM[rampos]));

                    //passa da l3 para ram
                    for (int i = 0; i < WORDS_SIZE; i++) //passa as palavras para a l3
                        cache3[l3pos].block.words[i] = RAM[rampos].words[i];
                    
                    //passa a tag da ram para l3
                    cache3[l3pos].tag = RAM[rampos].enderecoEmDisco;
                }
                cache3[l3pos] = cache2[l2pos];
                #if defined LFU || defined LRU || defined FIFO
                    reiniciaContador(&machine->l3, l3pos);
                #endif 

            }
            cache2[l2pos] = cache1[l1pos]; //cache 1 pra cache2
            #if defined LFU || defined LRU || defined FIFO
                reiniciaContador(&machine->l2, l2pos);
            #endif 
        }

        //passa da ram para l1
        for (int i = 0; i < WORDS_SIZE; i++) //passa as palavras para a l3
            cache1[l1pos].block.words[i] = RAM[rampos].words[i];
        
        //passa a tag da ram para l1
        cache1[l1pos].tag = RAM[rampos].enderecoEmDisco;

        cache1[l1pos].tag = add.block;
        cache1[l1pos].updated = false;
        cache1[l1pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM + COST_ACCESS_DISK;
        cache1[l1pos].cacheHit = 5;
        
        #if defined LFU || defined LRU || defined FIFO
            reiniciaContador(&machine->l1, l1pos);
        #endif 
    }
    updateMachineInfos(machine, cache1[l1pos].cacheHit, cache1[l1pos].cost);
    return &(cache1[l1pos]);
}
