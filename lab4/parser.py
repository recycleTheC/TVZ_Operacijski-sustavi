import re
import matplotlib.pyplot as plt

class Mjerenje:
	def __init__(self, order:int, size:int, real:int, user:int, sys:int):
		self.order = order
		self.size = size
		self.real = real
		self.user = user
		self.sys = sys

def obradi_mjerenja(izvor, rezultat):
	for i in range(0, len(izvor), 4):
		redni,velicina = izvor[i].split(",")
		
		minute,sekunde,stotinke = re.findall('[0-9]+', izvor[i+1])
		realno_vrijeme = float(minute) * 60 + float(sekunde) + float(stotinke) / 100
		
		minute,sekunde,stotinke = re.findall('[0-9]+', izvor[i+2])
		user_vrijeme = float(minute) * 60 + float(sekunde) + float(stotinke) / 100
		
		minute,sekunde,stotinke = re.findall('[0-9]+', izvor[i+3])
		sistemsko_vrijeme = float(minute) * 60 + float(sekunde) + float(stotinke) / 100
		
		rezultat.append(Mjerenje(int(redni), int(velicina), realno_vrijeme, user_vrijeme, sistemsko_vrijeme))

def prosjek(mjerenja:list):
	real = 0.0
	user = 0.0
	sys = 0.0
	n = len(mjerenja)
	
	for x in mjerenja:
		real += x.real
		user += x.user
		sys += x.sys
	
	return (real/n, user/n, sys/n)

def ispis_mjerenja(mjerenja:list, velicina:int):
	print("{:=^10}{:=^10}{:=^10}".format(" real ", " user ", " sys "))
	
	niz = [x for x in mjerenja if x.size == velicina]
	niz.sort(key=lambda x: x.real)
	
	for mjerenje in niz:
		print("{:^10.3f}{:^10.3f}{:^10.3f}".format(mjerenje.real, mjerenje.user, mjerenje.sys))
	print("="*30)
	real, user, sys = prosjek(niz)
	print("{:^10.3f}{:^10.3f}{:^10.3f}".format(real, user, sys))
	print("="*30)
	
mjerenja_procesi = []
mjerenja_dretve = []

procesi = [redak.strip() for redak in open("output/mjerenje-procesi.file") if redak != "\n"]
dretve = [redak.strip() for redak in open("output/mjerenje-dretve.file") if redak != "\n"]

obradi_mjerenja(procesi, mjerenja_procesi)
obradi_mjerenja(dretve, mjerenja_dretve)

for velicina in [1, 10, 100, 1000, 10000, 100000]:
	print("{:=^30}".format(" {} procesa ".format(velicina)))
	ispis_mjerenja(mjerenja_procesi, velicina)
print()
for velicina in [1, 10, 100, 1000, 10000, 100000]:
	print("{:=^30}".format(" {} dretvi ".format(velicina)))
	ispis_mjerenja(mjerenja_dretve, velicina)

# crtanje real time

mjerenja_procesi.sort(key=lambda x: x.real);
mjerenja_dretve.sort(key=lambda x: x.real);

plt.figure("Realno vrijeme izvršavanja (1)")
plt.plot([x.real for x in mjerenja_procesi], [y.size for y in mjerenja_procesi], color='red', label='procesi')
plt.plot([x.real for x in mjerenja_dretve], [y.size for y in mjerenja_dretve], color='green', label='dretve')
plt.xlabel("vrijeme potrebno za stvaranje (s)")
plt.ylabel("broj procesa / dretvi")
plt.title("realno vrijeme izvršavanja");
plt.legend()

#crtanje user time

mjerenja_procesi.sort(key=lambda x: x.user);
mjerenja_dretve.sort(key=lambda x: x.user);

plt.figure("Korisničko vrijeme izvršavanja (2)")
plt.plot([x.user for x in mjerenja_procesi], [y.size for y in mjerenja_procesi], color='red', label='procesi')
plt.plot([x.user for x in mjerenja_dretve], [y.size for y in mjerenja_dretve], color='green', label='dretve')
plt.xlabel("vrijeme potrebno za stvaranje (s)")
plt.ylabel("broj procesa / dretvi")
plt.title("korisničko vrijeme izvršavanja");
plt.legend()

#crtanje system time

mjerenja_procesi.sort(key=lambda x: x.sys);
mjerenja_dretve.sort(key=lambda x: x.sys);

plt.figure("Sistemsko vrijeme izvršavanja (3)")
plt.plot([x.sys for x in mjerenja_procesi], [y.size for y in mjerenja_procesi], color='red', label='procesi')
plt.plot([x.sys for x in mjerenja_dretve], [y.size for y in mjerenja_dretve], color='green', label='dretve')
plt.xlabel("vrijeme potrebno za stvaranje (s)")
plt.ylabel("broj procesa / dretvi")
plt.title("sistemsko vrijeme izvršavanja");
plt.legend()

plt.show()
