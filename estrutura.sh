# git clone https://github.com/mrjvs/42cursus_gnl_tests
caminho=$(pwd)
mkdir testeum
git clone https://github.com/mrjvs/42cursus_gnl_tests testeum/repo
cp -r -v -n testeum/42cursus_gnl_tests/ testeum/copia
#echo $caminho
caminho=$(echo $caminho | sed 's/\//\\\//g')
#echo $caminho
cat refazer.sh | sed "s/fWU3KdermTW3n9FRbtXwZ7AM/$caminho/g" > temp; mv temp refazer.sh
