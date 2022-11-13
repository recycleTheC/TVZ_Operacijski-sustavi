import subprocess, sys, os

class Zapis:
	def __init__(self, tip:str, redni_broj:int):
		self.tip = tip
		self.redni_broj = redni_broj
		
class Mjerenje:
	def __init__(self):
		self.velicina = 0
		self.odstupanja = 0
		self.paritet = 0
		self.tipovi = ["Roditelj", "Dijete"]
	
	def odstupanje(self):
		return float(self.odstupanja) * 100 / self.velicina
	
	def tocnost(self):
		return 100 - self.odstupanje()
		
	def postavi_paritet(self, zapis:Zapis):
		if zapis.tip == self.tipovi[0]:
			self.paritet = 0
		elif zapis.tip == self.tipovi[1]:
			self.paritet = 1
		else:
			raise ValueError("Nesto nije u redu s ulaznom datotekom! Napravite rucnu provjeru...")
		
	def provjeri_zapis(self, zapis:Zapis):
		self.velicina += 1
		
		if self.velicina == 1:
			self.postavi_paritet(zapis)
		elif zapis.tip != self.predvidi_tip_zapisa():
			self.odstupanja += 1
		
	def zavrsi(self):
		if self.velicina % 2 == 0 and self.odstupanja % 2 == 0:
			self.odstupanja //= 2
			self.velicina //=  2
		else:
			raise ValueError("Nesto nije u redu s ulaznom datotekom! Napravite rucnu provjeru...")

	def predvidi_tip_zapisa(self):
		if self.velicina % 2 == 0:
			if self.paritet == 0:
				return self.tipovi[1]
			else:
				return self.tipovi[0]
		else:
			return self.tipovi[self.paritet]

if len(sys.argv) >= 2 and sys.argv[1].isnumeric():
	ponavljanje = int(sys.argv[1])
else:
	ponavljanje = 1
	
if os.path.exists("output") == False:
	os.mkdir("output")
	
mjerenja = []
	
for i in range(0,ponavljanje):
	
	print("\n{}. iteracija:".format(i+1))
	
	for velicina in [10, 100, 1000, 10000, 100000]:
		try:
			putanja = "output/mjerenje-{}.file".format(velicina)
			datoteka = open(putanja, "w+")
			
			print("\n{:=^30}".format(" Mjerenje za {} djece ".format(velicina)))
			
			subprocess.run(["./lab2.out", str(velicina)], stdout=datoteka)
			datoteka.seek(0)

			mjerenje = Mjerenje()

			for linija in datoteka:
				tip, broj = linija.strip().split(" #")
				mjerenje.provjeri_zapis(Zapis(tip, int(broj)))

			mjerenje.zavrsi()
			
			print("Broj odstupanja: {odstupanja:d}".format(odstupanja=mjerenje.odstupanja))
			print("Broj izvodjenja: {izvodjenja:d}".format(izvodjenja=mjerenje.velicina))

			if mjerenje.odstupanja > 0:
				print("\nOdstupanje: {odstupanje:.3f}%".format(odstupanje=mjerenje.odstupanje()))
				print("Tocnost: {tocnost:.3f}%".format(tocnost=mjerenje.tocnost()))

			print("{:=^30}".format(" Kraj mjerenja ".format(velicina)))
			datoteka.close()
			mjerenja.append(mjerenje)

		except FileNotFoundError:
			print("Nije moguće otvoriti datoteku!")
		except ValueError as ex:
			print(ex.message)

mjerenja.sort(key=lambda mjerenje: mjerenje.velicina)

print("\n[{:*^28}]".format(" Sažetak mjerenja "))

for velicina in [10, 100, 1000, 10000, 100000]:
	print("{:=^30}".format(" {} procesa djece ".format(velicina)))
	print("{:=^20}{:=^10}".format(" odstupanja ", " točnost "))
	print("{:^10}{:^10}{:^10}".format(" broj ", " % ", " % "))
	
	for mjerenje in filter(lambda m: m.velicina == velicina, mjerenja):
		print("{:^10}{:^10.3f}{:^10.3f}".format(mjerenje.odstupanja, mjerenje.odstupanje(), mjerenje.tocnost()))
	print("="*30)
