'''
Created on 06/11/2016

#@author: ernesto
'''
import math
import logging

'''
Created on 06/11/2016

#@author: ernesto
https://www.hackerrank.com/challenges/closest-numbers/submissions/code/31624162
'''

import sys

nivel_log = logging.ERROR
# nivel_log = logging.DEBUG
logger_cagada = None

mediano_act = None
contador_mierda = 0

# @profile
def binary_search(seq, t, inic=None, fina=None):
    global contador_mierda
    if(inic is None):
        mini = 0
        maxi = len(seq) - 1
    else:
        mini = inic
        maxi = fina - 1
    logger_cagada.debug("mini %u maxi %u" % (mini, maxi))
    logger_cagada.debug("la seq es %s" % seq)
    while (maxi - mini >= 2):
        contador_mierda += 1
        m = (mini + maxi) >> 1
        if seq[m] < t:
            mini = m + 1
        else:
            maxi = m - 1
        
    logger_cagada.debug("despues del bucle mini %u maxi %u" % (mini, maxi))
    if(t >= seq[maxi]):
        return maxi + 1
    if(t >= seq[mini]):
        return maxi
    return mini

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
    
# @profile
def fraude_fuck_insertar_num(numeros, num_nuev, medi_ano):
    global contador_mierda
    idx_inser = 0
#    for idx_inser in range(len(numeros)):
#        if(num_nuev < numeros[idx_inser]):
#            break
#    if(idx_inser == len(numeros) - 1 and num_nuev >= numeros[-1]):
#        idx_inser += 1
    tam_numeros = len(numeros)
    mitad_numes = tam_numeros >> 1
    if(num_nuev > medi_ano):
        idx_inser = binary_search(numeros, num_nuev, mitad_numes + 1, tam_numeros)
    else:
        if(num_nuev < medi_ano):
            idx_inser = binary_search(numeros, num_nuev, 0, mitad_numes)
        else:
            idx_inser = mitad_numes
        
    numeros.insert(idx_inser , num_nuev)

def fraude_fuck_eliminar_num(numeros, viejo_pendejo):
    idx_elim = numeros.index(viejo_pendejo)
    del numeros[idx_elim]

# @profile
def fraude_fuck_core(numeros, nuevo_num, viejo_pendejo):
    medi_ano = 0
    tam_nums = len(numeros)
    
    global mediano_act
    
    if(viejo_pendejo == nuevo_num):
        if(mediano_act is None):
            if(tam_nums % 2):
                medi_ano = numeros[tam_nums >> 1]
            else:
                medi_ano = (numeros[(tam_nums >> 1) - 1] + numeros[(tam_nums >> 1)]) / 2
            mediano_act = medi_ano
        if(nuevo_num >= 2 * mediano_act):
            return 1
        return 0
        
    fraude_fuck_eliminar_num(numeros, viejo_pendejo)
    fraude_fuck_insertar_num(numeros, nuevo_num, mediano_act)

    if(viejo_pendejo >= mediano_act and nuevo_num >= mediano_act or viejo_pendejo < mediano_act and nuevo_num < mediano_act):
        if(nuevo_num >= 2 * mediano_act):
            return 1
        return 0
         
    if(tam_nums % 2):
        medi_ano = numeros[tam_nums >> 1]
    else:
        medi_ano = (numeros[(tam_nums >> 1) - 1] + numeros[(tam_nums >> 1)]) / 2
        
    logger_cagada.debug("medi ano doble %s, mas grande %u" % (medi_ano, numeros[-1]))
    mediano_act = medi_ano
        
    if(nuevo_num >= 2 * medi_ano):
        return 1
    return 0

# @profile
def fraude_fuck_main():
        contador_alerts = 0
        lineas = list(sys.stdin)
        _, tam_muest = [int(x) for x in lineas[0].strip().split(" ")]
        numeros = [int(x) for x in lineas[1].strip().split(" ")]

#        numeros_ord=sorted(numeros)
        numeros_ord = insert_sort(numeros[:tam_muest])
        logger_cagada.debug("numeros %s" % numeros)
      
        idx_sig_a_borrar = 0
        contador_alerts = fraude_fuck_core(numeros_ord, 0, 0)
        
        for nume in numeros[tam_muest:]:
            num_borr = numeros[idx_sig_a_borrar]
            logger_cagada.debug("nums ord %s entra %u sale %u" % (numeros_ord, nume, num_borr))
            contador_alerts += fraude_fuck_core(numeros_ord, nume, num_borr)
            logger_cagada.debug("contad es %u" % contador_alerts)
            idx_sig_a_borrar += 1

        logger_cagada.debug("MIERDA %u" % contador_mierda)
        print("MIERDA %u" % contador_mierda)
        print("%u" % contador_alerts)

if __name__ == "__main__":
    
        FORMAT = "[%(filename)s:%(lineno)s - %(funcName)20s() ] %(message)s"
        logging.basicConfig(level=nivel_log, format=FORMAT)
        logger_cagada = logging.getLogger("asa")
        logger_cagada.setLevel(nivel_log)
        fraude_fuck_main()
