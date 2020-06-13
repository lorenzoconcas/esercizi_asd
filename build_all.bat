echo off
mkdir bin
cls
echo ASD Lab projects builder script
echo Clearing workspace

cd bin
rm -f *.exe

cd ..

echo Bulding projects...

gcc "01 - Ricette"/main.c                           -o 1A_ricette.exe
gcc "01 - SelectionSort"/main.c                     -o 1_ssort.exe
gcc "02 - Ricerca Binaria"/main.c                   -o 2_ric_bin.exe
gcc "03 - Matrici Sparse"/main.c                    -o 3_matrici_sparse.exe
gcc "04 - Pattern Matching"/main.c                  -o 4_pattern_matching.exe
gcc "05 - Liste"/main.c                             -o 5_liste.exe
gcc "06 - Liste Doppiamente Concatenate"/main.c     -o 6_liste_d_c.exe
gcc "07 - Code"/main.c                              -o 7_code.exe
gcc "08 - ABR"/main.c                               -o 8_abr.exe
gcc "09 - Grafo"/main.c                             -o 9_grafo.exe
gcc "10 - Hash Table"/main.c                        -o 10_hash_table.exe
gcc "11 - InsertionQuickSort"/main.c                -o 11_insertionquicksort.exe
gcc "12 - Heap Merge"/main.c                        -o 12_heap_merge.exe

echo Moving to bin folder...

move *.exe                  bin     >nul
echo Files moved
cd bin
dir
cd ..

echo Done!
