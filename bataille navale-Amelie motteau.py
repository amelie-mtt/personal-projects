
'mise à zero des variables'
memoire = 0           # permet de compter les coups
bx1=0                 # coordonnées en x du premier bateau
bx2=0                 # coordonnées en x du deuxième bateau 
by1=0                 # coordonnées en y du premier bateau
by2=0                 # coordonnées en y du deuxi-ème bateau
tx=0                  # valeur recherche en x
ty=0                  # valeur recherche en y



print ('                Jeu de bataille navale')


print ('  ')
print ('saisir les coordonnées du premier bateau')
print ('  ')
'saisie position du bateau'
while (bx1>3 or bx1<1):                      # boucle pour saisie hors tableau
   print ("premiere coordonnées :Saisir un nombre entre 1 et 3")
   bx1 = input("? : ")
   try :                                          # evite la plantage si saisie d'une lettre
       bx1 = int(bx1)                             # conversion de bx1 en integer
   except :
       bx1 = 10                                   # met la valeur à 10 si plantage
   if (bx1>3 or bx1<1): print ('mauvaise saisie: recommencer')
     
while (by1>3 or by1<1):                      # boucle pour saisie hors tableau
    print ("deuxième coordonnées :Saisir un nombre entre 1 et 3")
    by1=input(" ? : ")
    try:                                          # evite le plantage si saisie d'une lettre
        by1 = int(by1)                            # conversion de by1 en interger
    except : 
        by1 = 10                                  # met la valeur à 10 si plantage
    if (by1>3 or by1<1): print ('mauvaise saisie: recommencer')
    
print ('  ')
print ('saisir les coordonnées du second bateau')
while (bx2>3 or bx2<1):                      # boucle pour saisie hors tableau
    print ("premiere coordonnées :Saisir un nombre entre 1 et 3")
    bx2= input(" ? : ")
    try :                                         # evite la plantage si saisie d'une lettre
        bx2 = int(bx2)                            # conversion de bx1 en integer
    except :
        bx2 = 10                                      # met la valeur à 10 si plantage 
    if (bx2>3 or bx2<1): print ('mauvaise saisie: recommencer')
    
while (by2>3 or by2<1):                      # boucle pour saisie hors tableau
    print ("deuxième coordonnées :Saisir un nombre entre 1 et 3")
    by2= input(" ? : ")
    try :                                         # evite la plantage si saisie d'une lettre  
        by2 = int(by2)                            # conversion de bx1 en integer
    except :
        by2 = 10                                  # met la valeur à 10 si plantage
    if (by2>3 or by2<1): print ('mauvaise saisie: recommencer')



print ('  ')
print('tentez votre chance')
while (bx1!=0 or bx2!=0):
    print ('  ')
    print ("Saisir un nombre entre 1 et 3")
    tx= input(" ? : ")
    try :                                         # evite la plantage si saisie d'une lettre
        tx = int(tx)                              # conversion de bx1 en integer
    except :
        tx=10                                     # met la valeur à 10 si plantage
    print ("Saisir un nombre entre 1 et 3")
    ty= input(" ? : ")
    try :                                         # evite la plantage si saisie d'une lettre
        ty = int(ty)                              # conversion de bx1 en integer
    except :
        ty=10                                     # met la valeur à 10 si plantage
    if (tx<1 or tx>3 or ty<1 or ty>3):  # commentaire si saisie hors tableau
        print ('vous avez perdu un coup, les coordonnées sont mauvaises')
    memoire=memoire+1
    if (tx==bx1 and ty==by1):
            print ('touche')
            bx1=0
            by1=0
              
    if (tx==bx2 and ty==by2):
            print ('touche')
            aleau=0
            bx2=0
            by2=0,
                          
print  ('gagné en',memoire, 'coups')


