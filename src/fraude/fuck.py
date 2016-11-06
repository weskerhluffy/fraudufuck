'''
Created on 06/11/2016

@author: ernesto
'''
import math
import logging

'''
Created on 06/11/2016

@author: ernesto
https://www.hackerrank.com/challenges/closest-numbers/submissions/code/31624162
'''

import sys

nivel_log = logging.ERROR
#nivel_log = logging.DEBUG
logger_cagada = None


def insert_sort(numeros):
        alist = list(numeros)
        for index in range(1, len(alist)):

                currentvalue = alist[index]
                position = index
                while position > 0 and alist[position - 1] > currentvalue:
                        alist[position] = alist[position - 1]
                        position = position - 1

                alist[position] = currentvalue

        return alist
    
def fraude_fuck_insertar_num(numeros, num_nuev):
    idx_inser = 0
    for idx_inser in range(len(numeros)):
        if(num_nuev < numeros[idx_inser]):
            break
            
    if(idx_inser == len(numeros) - 1 and num_nuev >= numeros[-1]):
        idx_inser += 1
        
    numeros.insert(idx_inser , num_nuev)

def fraude_fuck_eliminar_num(numeros, viejo_pendejo):
    idx_elim = numeros.index(viejo_pendejo)
    del numeros[idx_elim]

def fraude_fuck_core(numeros, nuevo_num, viejo_pendejo):
    medi_ano = 0
    tam_nums = len(numeros)
    if(viejo_pendejo != nuevo_num):
        fraude_fuck_eliminar_num(numeros, viejo_pendejo)
        fraude_fuck_insertar_num(numeros, nuevo_num)
    
    if(tam_nums % 2):
        medi_ano = numeros[tam_nums >> 1]
    else:
        medi_ano = (numeros[(tam_nums >> 1) - 1] + numeros[(tam_nums >> 1)]) / 2
        
    logger_cagada.debug("medi ano doble %s, mas grande %u" % (medi_ano, numeros[-1]))
        
    if(nuevo_num >= 2 * medi_ano):
        return 1
    return 0

@profile
def fraude_fuck_main():
        contador_alerts = 0
        lineas = list(sys.stdin)
        _, tam_muest = [int(x) for x in lineas[0].strip().split(" ")]
        numeros = [int(x) for x in lineas[1].strip().split(" ")]
        logger_cagada.debug("numeros %s" % numeros)

#        numeros_ord=sorted(numeros)
        numeros_ord = insert_sort(numeros[:tam_muest])
        
        idx_sig_a_borrar = 0
        logger_cagada.debug("nums ord original %s " % numeros_ord)
        contador_alerts = fraude_fuck_core(numeros_ord, 0, 0)
        
        for nume in numeros[tam_muest:]:
            logger_cagada.debug("nums ord %s entra %u sale %u" % (numeros_ord, nume, numeros[idx_sig_a_borrar]))
            contador_alerts += fraude_fuck_core(numeros_ord, nume, numeros[idx_sig_a_borrar])
            logger_cagada.debug("contad es %u" % contador_alerts)
            idx_sig_a_borrar += 1

        print("%u" % contador_alerts)

if __name__ == "__main__":
    
        FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
        logging.basicConfig(level=nivel_log, format=FORMAT)
        logger_cagada = logging.getLogger("asa")
        logger_cagada.setLevel(nivel_log)
        fraude_fuck_main()
