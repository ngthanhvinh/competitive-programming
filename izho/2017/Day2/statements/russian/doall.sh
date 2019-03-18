cd ../../problems/gerland/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/bombs/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/perfect-leafs/statements/russian
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

latex statements.tex
latex statements.tex
dvips statements.dvi
dvipdfmx -p a4 statements.dvi
rm -f *.log
rm -f *.aux
rm -f *.dvi
rm -f *.ps
