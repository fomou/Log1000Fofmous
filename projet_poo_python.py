class Employee:
    def __init__(self,nom,salaire):
        self.nom=nom
        self.salaire=salaire
    def getNom(self):
        return self.nom
    def getSalaire(self):
        return self.salaire
    def afficher(self):
        print("le nom de l'employé est:",self.getNom(),"\n")
        print("le salaire de l'employé est:",self.getSalaire(),"\n")

        
#--------main-------#
        
   


        
