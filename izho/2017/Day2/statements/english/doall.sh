cd ../../problems/gerland/statements/english
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/bombs/statements/english
for file in ./*.mp
do
    mpost $file
done
rm -f *.log
cd -

cd ../../problems/perfect-leafs/statements/english
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
