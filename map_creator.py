#!/usr/bin/python3

################################################################################
# wta & awoimbee | Wolf3D Map Generator                                        #
################################################################################

import tkinter as tk
import sys

class Player:
    def __init__(self, isSet=False, pos=(0, 0)):
        self.isSet = isSet
        self.pos = pos

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
            if board[row][column] == 1:
                canvas.create_rectangle(
                    x,
                    y,
                    x+caseSize,
                    y+caseSize,
                    fill="black",
                    tag="cell",
                    outline="grey"
                )
            elif board[row][column] == 64:
                canvas.create_rectangle(
                    x,
                    y,
                    x+caseSize,
                    y+caseSize,
                    fill="green",
                    tag="cell",
                    outline="grey"
                )
            x += caseSize
            if x >= mapWidth*caseSize:
                x = 0
        y += caseSize

def is_not_border(x, y):
    return 0 < y < mapHeight - 1 and 0 < x < mapWidth - 1


def placeThing(event):
    ## canvas coordinates -> last_dragboard coordinates
    event.x //= caseSize
    event.y //= caseSize

    if event.state != 0:
        if placeThing.lastDrag == (event.x, event.y, event.state):
            return
        else:
            placeThing.lastDrag = (event.x, event.y, event.state)

    if is_not_border(event.x, event.y):
        isPlayerLoc = board[event.y][event.x] == 64
        ## Left click
        if event.state == 256 or event.num == 1:
            if isPlayerLoc:
                player.isSet = False
            board[event.y][event.x] = int(not board[event.y][event.x])
        elif event.num == 3 or event.state == 1024:
            ## Right click
            if not isPlayerLoc:
                board[event.y][event.x] = 64
                if player.isSet:
                    board[player.pos[1]][player.pos[0]] = 0
                player.isSet = True
                player.pos = (event.x, event.y)
            else:
                board[event.y][event.x] = 0
                player.isSet = False
    #Affichage
    display()
placeThing.lastDrag = -1


def clearAll():
    "Efface toute les cellules"
    global board, player
    #Ré-initialisation des étapes
    board = [[0 if is_not_border(i, j) else 1 for i in range(mapWidth)] for j in range(mapHeight)]
    player.isSet = False
    #Affichage
    display()

def saveFile():
    if player.isSet:
        mapFile = open("./map", "w")
        mapFile.write(str(mapWidth) + " " + str(mapHeight) + "\n")
        #Parcours du tableau de long en large
        for row, _ in enumerate(board):
            for column, _ in enumerate(board[0]):
                #On trace seulement si la case est vivante
                if board[row][column] == 1:
                    mapFile.write("1")
                elif board[row][column] == 64:
                    mapFile.write("@")
                else:
                    mapFile.write("0")
            mapFile.write("\n")
        mapFile.close()
        print("You can now run:\n\t./wolf3d map")
        root.destroy()
    else:
        errorMsg.set("You need to set the spawn point!")


def setMapSize():
    global askWin, mapWidth, mapHeight

    tmpW = int(askSize.e_w.get())
    tmpH = int(askSize.e_h.get())
    if 4 < tmpW <= 400 and 4 < tmpH <= 400:
        mapWidth = tmpW
        mapHeight = tmpH
        askWin.destroy()
    else:
        print("Bad dimensions !")

def askSize():
    global askWin
    askWin = tk.Tk()
    askWin.title("Quelles dimensions ?")
    #Ajout de 2 champs de saisie à la fenêtre
    askSize.e_w = tk.Entry(askWin)
    askSize.e_w.grid(row=1, column=1, padx=3, pady=3)
    askSize.e_h = tk.Entry(askWin)
    askSize.e_h.grid(row=1, column=3, padx=3, pady=3)
    #Ajout d'un bouton à la fenêtre
    ok_button = tk.Button(askWin, text="OK", command=setMapSize)
    askWin.bind("<Return>", setMapSize)
    ok_button.grid(row=2, column=2, padx=3, pady=3)
    askWin.mainloop()

##########################################
#          PROGRAMME PRINCIPAL           #
##########################################

if __name__ == "__main__":
    global mapWidth, mapHeight
    ######## INIT VARS ########
    player = Player()
    if len(sys.argv) != 3:
        print(
            "You can directly specify the width and height:\n"
            "./map_creator.py <width> <height>"
        )
        askSize()
    else:
        mapWidth = int(sys.argv[1])
        mapHeight = int(sys.argv[2])
    if mapWidth < 4 or mapHeight < 4 or mapWidth > 400 or mapHeight > 400:
        print("Invalid map size")
        sys.exit(0)
    caseSize = int(max(-0.15 * max(mapWidth, mapHeight * (16/9)) + 30, 4))
    board = [[0 if is_not_border(i, j) else 1 for i in range(mapWidth)] for j in range(mapHeight)]

    ######## INIT WINDOW ########
    root = tk.Tk()
    root.title("Wolf3D map generator")
    root.configure(background="grey")
    ## Board canvas
    canvas = tk.Canvas(
        root,
        width=caseSize*mapWidth,
        height=caseSize*mapHeight,
        bg="white",
        bd=0,
        highlightthickness=0
    )
    canvas.grid(column=1, row=1, padx=2, pady=2, columnspan=100)
    canvas.bind("<Button-1>", placeThing) #Localisation des clics dans le canvas3
    canvas.bind("<B1-Motion>", placeThing)
    canvas.bind("<Button-3>", placeThing)
    canvas.bind("<B3-Motion>", placeThing)
    ## Buttons frame
    userPart = tk.LabelFrame(
        root,
        bd=2,
        text="Utilisateur",
        bg="grey",
        fg="white",
        font=("Calibri", 12)
    )
    userPart.grid(column=100, row=2, padx=5, pady=2, sticky=tk.W)
    ### Save button
    saveButton = tk.Button(
        userPart,
        text="sauvegarder",
        command=saveFile,
        bg="#545556",
        fg="white",
        relief="flat",
        font=("Calibri", 12)
    )
    saveButton.grid(column=1, row=1, padx=7, pady=5)
    ### Clear button
    clearButton = tk.Button(
        userPart,
        text="Tout effacer",
        command=clearAll,
        bg="#545556",
        fg="white",
        relief="flat",
        font=("Calibri", 12)
    )
    clearButton.grid(column=1, row=2, padx=7, pady=5)
    ### Info frame
    devPart = tk.LabelFrame(
        root,
        bd=2,
        text="Développeur",
        bg="grey",
        fg="white",
        font=("Calibri", 12)
    )
    devPart.grid(column=99, row=2, padx=5, pady=2, sticky=tk.W)
    errorMsg = tk.StringVar()
    errorMsg.set("")
    cDisp1 = tk.Label(devPart, textvariable=errorMsg, bg="grey", fg="red", font=("Calibri", 12))
    cDisp1.grid(column=1, row=1, padx=7, pady=5)
    ## :/
    root.resizable(False, False)
    ## Draw board lines
    for i in range(len(board[0])):
        canvas.create_line(i * caseSize, 0, i * caseSize, mapHeight * caseSize, fill="grey")
    for i in range(len(board)):
        canvas.create_line(0, i * caseSize, mapWidth * caseSize, i * caseSize, fill="grey")
    ## Events loop
    display()
    root.mainloop()
