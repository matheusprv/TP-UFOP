#include "mmu.h"

#include <stdio.h>

bool canOnlyReplaceBlock(Line line) {
    // Or the block is empty or
    // the block is equal to the one in memory RAM and can be replaced
    if (line.tag == INVALID_ADD || (line.tag != INVALID_ADD && !line.updated))
        return true;
    return false;
}

int memoryCacheMapping(int address, Cache* cache) {   
    #ifdef MAPEAMENTO_DIRETO
        return address % cache->size;
    #endif

    #ifdef MAPEAMENTO_ASSOCIATIVO
        
        for(int i=0; i<cache->size; i++){
            //Varre a cache, procurando a tag que contem o endereco desejado
            if(address == cache->lines[i].tag){
                return i;
            }
        }
        return 0;
    
    #endif
}

//Varre o vetor de linhas da cache 
int procurarBlocoASair(Cache* cache){

    //Verificando se há posições vazias na cache. Caso tenha, retorna a posição vazia
    for(int i = 0; i < cache->size; i++){
        if(cache->lines[i].tag == -1)
            return i;
    }

    int posicao = 0;

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

    return posicao;
}

void updateMachineInfos(Machine* machine, Line* line) {
    switch (line->cacheHit) {
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
    }
    machine->totalCost += line->cost;
}

Line* MMUSearchOnMemorys(Address add, Machine* machine) {
    // Strategy => write back
    
    // Mapeamento da memoria
    int l1pos = memoryCacheMapping(add.block, &machine->l1);
    int l2pos = memoryCacheMapping(add.block, &machine->l2);
    int l3pos = memoryCacheMapping(add.block, &machine->l3);


    Line* cache1 = machine->l1.lines;
    Line* cache2 = machine->l2.lines;
    Line* cache3 = machine->l3.lines;

    MemoryBlock* RAM = machine->ram.blocks;

    if (cache1[l1pos].tag == add.block) { 
        /* Block is in memory cache L1 */
        cache1[l1pos].cost = COST_ACCESS_L1;
        cache1[l1pos].cacheHit = 1;
        cache1[l1pos].contador += 1;
    } 
    else if (cache2[l2pos].tag == add.block) { 
        /* Block is in memory cache L2 */
        cache2[l2pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2;
        cache2[l2pos].cacheHit = 2;
        cache2[l2pos].contador += 1;

        // !Can be improved?
        updateMachineInfos(machine, &(cache2[l2pos]));
        return &(cache2[l2pos]); 
    } 
    else if(cache3[l3pos].tag == add.block){

        cache3[l3pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3;
        cache3[l3pos].cacheHit = 3; 
        cache3[l3pos].contador += 1;
        
        updateMachineInfos(machine, &(cache3[l3pos]));
        return &(cache3[l3pos]);
    } 
    else { 
        /* Bloco somente na RAM, precisa leva-lo para a cache e manipular os blocos */
        
        //Procurando os blocos que podem sair de cada linha
        l1pos = procurarBlocoASair(&machine->l1);
        l2pos = procurarBlocoASair(&machine->l2);
        l3pos = procurarBlocoASair(&machine->l3);
        
        //Procurando a posicao do bloco que vai sair da l2
        //l3pos = memoryCacheMapping(cache2[l2pos].tag, &machine->l3);
        
        if (!canOnlyReplaceBlock(cache1[l1pos])) { 
            /* The block on cache L1 cannot only be replaced, the memories must be updated */
            if (!canOnlyReplaceBlock(cache2[l2pos])) {
                
                if (!canOnlyReplaceBlock(cache3[l3pos])) {
                    RAM[cache3[l3pos].tag] = cache3[l3pos].block;
                }
                cache3[l3pos] = cache2[l2pos];
            }
            cache2[l2pos] = cache1[l1pos]; //cache 1 pra cache2
        }
        cache1[l1pos].block = RAM[add.block];
        cache1[l1pos].tag = add.block;
        cache1[l1pos].updated = false;
        cache1[l1pos].cost = COST_ACCESS_L1 + COST_ACCESS_L2 + COST_ACCESS_L3 + COST_ACCESS_RAM;
        cache1[l1pos].cacheHit = 4;
    }
    updateMachineInfos(machine, &(cache1[l1pos]));
    return &(cache1[l1pos]);
}
