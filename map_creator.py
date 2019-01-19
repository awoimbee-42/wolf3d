

################################################################################
# wta & awoimbee | Wolf3D Map Generator                                        #
################################################################################


#Importation de divers modules utiles
from tkinter import *
from random import randint
import time


class Player:
    def __init__(self, isSet = False, pos = (0, 0)):
        self.isSet = isSet
        self.pos = pos

##########################################
#              FONCTIONS                 #
##########################################
def display():
    "Affiche un tableau dans le canvas à partir de la liste"
    global board

    #Effacer toute les cellules
    canvas.delete("cell")

    #Coordonnées dans le canvas qui servent à placer les carrés
    x, y = 0, 0
    #Parcours du tableau de long en large
    for row in range(len(board)):
        for column in range(len(board[0])):
            #On trace seulement si la case est vivante
            if board[row][column] == 1:
                canvas.create_rectangle(x, y, x+caseSize, y+caseSize, fill="black", tag="cell", outline="grey")
            elif board[row][column] == 64:
                canvas.create_rectangle(x, y, x+caseSize, y+caseSize, fill="green", tag="cell", outline="grey")
            #On passe a la cellule suivante
            x += caseSize
            #Retour à la ligne
            if x >= mapWidth*caseSize:
                x = 0
        y += caseSize

def isntBorder(x, y):
    return (y > 0 and y < mapHeight - 1 and x > 0 and x < mapWidth - 1)


def placeThing(event):
    "Change la couleur de la case cliquée"
    global last_drag;

    #Calcul et affichage des coordonnées dans la case dans le tableau
    event.x //= caseSize
    event.y //= caseSize

    if event.state != 0:
        if last_drag == (event.x, event.y, event.state):
            return
        else:
            last_drag = (event.x, event.y, event.state)

    if isntBorder(event.x, event.y):
        #click gauche
        if event.state == 256 or event.num == 1:
            #Si on clique sur une case blanche, elle devient noire
            if board[event.y][event.x] != 1:
                board[event.y][event.x] = 1
            #Si on clique sur une case noire, elle devient blanche
            elif board[event.y][event.x] == 1:
                board[event.y][event.x] = 0
        elif event.num == 2 or event.state == 512:
            #click droit
            if board[event.y][event.x] != 64:
                board[event.y][event.x] = 64
                if isPlayerSet.isSet == True:
                    board[isPlayerSet.pos[1]][isPlayerSet.pos[0]] = 0
                isPlayerSet.isSet = True
                isPlayerSet.pos = (event.x, event.y)
            else:
                board[event.y][event.x] = 0
                isPlayerSet.isSet = False
    #Affichage
    display()



def clearAll():
    "Efface toute les cellules"
    global board, step
    #Ré-initialisation des étapes
    step = 0
    board = [[0 if isntBorder(j, i) else 1 for i in range(mapWidth)] for j in range(mapHeight)]
    #Affichage
    display()

def saveFile():
    if (isPlayerSet.isSet):
        mapFile = open("./map", "w")
        mapFile.write(str(mapWidth) + " " + str(mapHeight) + "\n")
        x, y = 0, 0
        #Parcours du tableau de long en large
        for row in range(len(board)):
            for column in range(len(board[0])):
                #On trace seulement si la case est vivante
                if board[row][column] == 1:
                    mapFile.write("1")
                elif board[row][column] == 64:
                    mapFile.write("@")
                else:
                    mapFile.write("0")
            mapFile.write("\n")
        mapFile.close()
    else:
        errorMsg.set("You need to set the spawn point!")


def setMapSize():
    global askWin, mapWidth, mapHeight, widthE, heightE

    tmpW = int(widthE.get())
    tmpH = int(heightE.get())
    if 4 < tmpW <= 400 and 4 < tmpH <= 400:
        mapWidth = tmpW
        mapHeight = tmpH
        askWin.destroy()
    else:
        print("Bad dimensions !")

def askSize():
    global askWin, widthE, heightE
    askWin = Tk()
    askWin.title("Quelles dimensions ?")
    #Ajout de 2 champs de saisie à la fenêtre
    widthE = Entry(askWin)
    widthE.grid(row=1, column=1, padx=3, pady=3)
    heightE = Entry(askWin)
    heightE.grid(row=1, column=3, padx=3, pady=3)
    #Ajout d'un bouton à la fenêtre
    boutonOk = Button(askWin, text="OK", command=setMapSize)
    boutonOk.grid(row=2, column=2, padx=3, pady=3)
    askWin.mainloop()

##########################################
#          PROGRAMME PRINCIPAL           #
##########################################

if __name__ == "__main__":

    ######## INITIALISATION DES VARIABLES ########
    isPlayerSet = Player()
    last_drag = -1
    #Taille d'une case en pixels
    caseSize = 20
    #Largeur du tableau
    mapWidth = 1
    mapHeight = 1
    askSize()
    if mapWidth < 4 or mapHeight < 4:
        exit(0)
    elif mapWidth > 256 or mapHeight > 256:
        caseSize = 2
    elif mapWidth > 128 or mapHeight > 128:
        caseSize = 5
    elif mapWidth > 90 or mapHeight > 90:
        caseSize = 10
    elif mapWidth > 60 or mapHeight > 60:
        caseSize = 15
    #Initialisation de la fenêtre
    root = Tk()
    root.title("Wolf3D map generator")
    #Fond de la fenêtre
    root.configure(background="grey")
    #Initialisation du tableau
    board = [[0 if isntBorder(j, i) else 1 for i in range(mapWidth)] for j in range(mapHeight)]

    ######## TABlEAU ########
    canvas = Canvas(root, width=caseSize*mapWidth, height=caseSize*mapHeight, bg="white", bd=0, highlightthickness=0)
    canvas.grid(column=1, row=1, padx=2, pady=2, columnspan=100)
    canvas.bind("<Button-1>", placeThing) #Localisation des clics dans le canvas3
    canvas.bind("<B1-Motion>", placeThing)
    canvas.bind("<Button-2>", placeThing)
    canvas.bind("<B2-Motion>", placeThing)

    ######## INTERFACE INTERACTIONS UTILISATEUR/PROGRAMME ########
    userPart = LabelFrame(root, bd=2, text="Utilisateur", bg="grey", fg="white", font=("Calibri", 12))
    userPart.grid(column=100, row=2, padx=5, pady=2, sticky=W)
    #Bouton de save
    saveButton = Button(userPart, text="sauvegarder", command=saveFile, bg="#545556", fg="white", relief="flat", font=("Calibri", 12))
    saveButton.grid(column=1, row=1, padx=7, pady=5)
    #Bouton de clear
    clearButton = Button(userPart, text="Effacer tout", command=clearAll, bg="#545556", fg="white", relief="flat", font=("Calibri", 12))
    clearButton.grid(column=1, row=2, padx=7, pady=5)

    ######## INTERFACE INFORMATION ########
    devPart = LabelFrame(root, bd=2, text="Développeur", bg="grey", fg="white", font=("Calibri", 12))
    devPart.grid(column=99, row=2, padx=5, pady=2, sticky=W)

    errorMsg = StringVar()
    errorMsg.set("")
    cDisp1 = Label(devPart, textvariable=errorMsg, bg="grey", fg="red", font=("Calibri", 12))
    cDisp1.grid(column=1, row=1, padx=7, pady=5)

    #Fenêtre non-redimensionnable (provisoire)
    root.resizable(False, False)

    ######## TRACAGE DU QUADRILLAGE ########
    #Traçage du quadrillage vertical
    a,b = 0,0
    for i in range(len(board)):
        for j in range(len(board[0])):
            canvas.create_line(a, b, a, b+mapHeight*caseSize, fill="grey")
            a += caseSize
    #Traçage d'un quadrillage horizontal
    a, b = 0,0
    for i in range(len(board)):
        for j in range(len(board[0])):
            canvas.create_line(a, b, a+mapWidth*caseSize, b, fill="grey")
            b += caseSize


    #Activation du gestionnaire d'évènement de la fenêtre
    display()
    root.mainloop()
