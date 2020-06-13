@echo off
If not exist bin\ Exit /b
cls
cd bin
echo Scegli un esercizio
echo.
echo (1) Selection Sort
echo (1a) Ricette
echo (2) Ricerca Binaria
echo (3) Matrici Sparse
echo (4) Pattern Matching
echo (5) Liste
echo (6) Liste Doppiamente concatenate
echo (7) Code
echo (8) ABR
echo (9) Grafo
echo (10) Hash Table
echo (11) Quick-Insertion Sort
echo (12) Heap Merge

echo.

set /p chc="Scelta : "
IF "%chc%"=="1"     1_ssort
IF "%chc%"=="1a"    1A_ricette
IF "%chc%"=="2"     2_ric_bin
IF "%chc%"=="3"     3_matrici_sparse
IF "%chc%"=="4"     4_pattern_matching
IF "%chc%"=="5"     5_liste
IF "%chc%"=="6"     6_liste_d_c
IF "%chc%"=="7"     7_code
IF "%chc%"=="8"     8_abr
IF "%chc%"=="9"     9_grafo
IF "%chc%"=="10"    10_hash_table
IF "%chc%"=="11"    11_insertionquicksort
IF "%chc%"=="12"    12_heap_merge

cd ..
echo.
echo Goodbye
@echo on