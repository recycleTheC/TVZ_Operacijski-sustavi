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
	

mjerenja_procesi = []
mjerenja_dretve = []

procesi = [redak.strip() for redak in open("output/mjerenje-procesi.file") if redak != "\n"]
dretve = [redak.strip() for redak in open("output/mjerenje-dretve.file") if redak != "\n"]

mjerenja_procesi = []
mjerenja_dretve = []

procesi = [redak.strip() for redak in open("output/mjerenje-procesi.file") if redak != "\n"]
dretve = [redak.strip() for redak in open("output/mjerenje-dretve.file") if redak != "\n"]

obradi_mjerenja(procesi, mjerenja_procesi)
obradi_mjerenja(dretve, mjerenja_dretve)

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
