#!/bin/bash -xue


MYDIR="$(dirname "$0")"
DATADIR="${MYDIR}/data"
mkdir -p "${DATADIR}"
cd "${DATADIR}"


DATASOURCES=()
DATASOURCES+=("https://github.com/freeCodeCamp/freeCodeCamp/archive/refs/heads/main.zip")
DATASOURCES+=("https://github.com/logpai/loghub/archive/refs/heads/master.zip")

mkdir -p downloads
cd downloads

for ds in "${DATASOURCES[@]}"; do
    D=$(echo "${ds}" | md5sum | awk '{print $1}')
    if [ -d "${D}" ]; then
        continue
    fi
    TMP="${D}.tmp"
    rm -rf "${TMP}"
    mkdir "${TMP}"
    cd "${TMP}"
    wget "${ds}"
    unzip "*.zip"
    echo "${ds}" > source.txt
    cd ..
    mv ${TMP} ${D}
done



find . ! -name "*.zip" -type f -exec cat '{}' \; | \
    tr -c '[:digit:]' '\n' | grep . | \
    python3 -c 'import sys; [print (int(x)) for x in sys.stdin.readlines() if int(x) <= 0xffffffff]' | \
    sort | \
    uniq -c > ../data_real.txt

cd ..


#seq 100000 $((100000+1500000)) | awk '{print 1, $0}' > data_seq.txt

#cat /dev/urandom | od -A n -t d4 | tr  ' -' '\n' | grep . | head -n 1000000 | awk '{print 1, $0}' > data_random.txt

python3 <<EOF > data_random1.txt
import random
random.seed(2323429)
for _ in range(1000000):
    print (1, random.randint(0,0xffffffff))
EOF

python3 <<EOF > data_random2.txt
import random
random.seed(2323411)
for _ in range(1000000):
    w=random.randint(1,32)
    if w == 1:
        print (1, random.randint(0,1))
    else:
        print (1, (2**(w-1)) + random.randint(0,(2**(w-1))-1))
EOF
