#!/bin/bash
# Название рассчитываемой задачи. Может быть любым
#SBATCH --job-name="myHELLO"
#
#
# Множество вычислительных узлов для расчёта задачи
# Определяет характеристику вычислительных узлов (cluster partition)
#SBATCH --partition=debug
#
#
# Запускать рассчитываемую задачу на заданном здесь количестве узлов (<= 10)
#SBATCH --nodes=10
#
#
# Расчётное время, после истечения которого задача будет принудительно остановлена
# В данном случае -- 5 минут
#SBATCH --time=0-00:05:00
#
# В данном случае -- 7 дней (комментарий)
###SBATCH --time=7-00:00:00
#
#
# Количество потоков одного процессора (<= 1 для нашего кластера)
#SBATCH --ntasks-per-node=1
#
#
# Объём оперативной памяти, необходимой на каждом узле
# Единицы измерения по умолчанию -- Мегабайты (MB)
# Для нашего кластера это обязательное указание
# Это объём доступной на узле памяти
#SBATCH --mem=1992

# Чтобы srun заработал с impi (у нас пока нет)
### export I_MPI_PMI_LIBRARY=/usr/lib64/libpmi.so

mpirun -np 10 hello
