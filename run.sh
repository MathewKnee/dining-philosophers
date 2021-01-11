gcc philosopher.c -o philosopher

for i in {1..5}
do
    ./philosopher $i &
done