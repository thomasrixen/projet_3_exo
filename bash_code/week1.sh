
echo "Inserer" > first.txt
#cat first.txt >> second.txt
cp first.txt second.txt
echo "Retirer" >> second.txt
#ls -l
echo "" > third.txt
cat first.txt >> third.txt | cat second.txt >> third.txt
grep "Retirer" second.txt -n
cp -r ./ ../test_new
rm -r ../test_new
./exe/test
echo $?   #affiche le dernier résultat !!!!! 