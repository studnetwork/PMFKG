# https://knezevicmarko.github.io/os2/2017/213-pairRDD.html

from pyspark import SparkConf, SparkContext


def kategorisi(iznos, kat_granice):
    # pretpostavljamo da su kategorije sortirane ispravno
    for idx, granica in enumerate(kat_granice):
        if iznos < granica:
            return idx
    return len(kat_granice)
        

conf = SparkConf().setMaster('local').setAppName('domaci')
sc = SparkContext(conf=conf)

kat_granice = sc.textFile('kategorizacija.txt').map(lambda granica: float(granica)).collect()
kvartal1 = sc.textFile('kvartal1.txt')
kvartal2 = sc.textFile('kvartal2.txt')
kvartal3 = sc.textFile('kvartal3.txt')
kvartal4 = sc.textFile('kvartal4.txt')

tran_linije = kvartal1 \
    .union(kvartal2) \
    .union(kvartal3) \
    .union(kvartal4)

transakcije = tran_linije.map(lambda x: x.split())

# svaku transakciju (pib1, pib2, iznos) rastavlja na (pib1, iznos) i  (pib2, iznos)
transakcije_po_pib = transakcije.flatMap(lambda x: [(int(x[0]), float(x[2])), (int(x[1]), float(x[2]))])

kategorisane_tran = transakcije_po_pib.map(lambda x: (x[0], kategorisi(x[1], kat_granice)))
pib_kat_count = kategorisane_tran \
    .filter(lambda x: x[1] > 0) \
    .map(lambda x: (x, 1)).reduceByKey(lambda a, b: a+b)
pib_kat_count.map(lambda x: f'PIB: {x[0][0]:>4}; kategorija: {x[0][1]}; broj transakcija: {x[1]:>6}').saveAsTextFile('out')
