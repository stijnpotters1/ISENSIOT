# ISENSIOT-robot-arm



 This is an arduino directory for the hand gesture controlled robot arm


 ### Bluetooth configuratie:
 **Circuits**
 Gebruik tijdelijk voor de arduino uno dit circuit. 
 Na de bluetooth configuratie kan je dit weer terug veranderen naar het oude circuit.
![Schermafbeelding 2023-12-06 222613](https://github.com/stijnpotters1/ISENSIOT/assets/93516547/8198d485-c88b-475e-8183-aa937c45808f)


 **Slave (uno)**:

 1. Houdt het knopje van de bluetooth module in, waar je de slave van wilt maken (in ons geval de uno).
 2. Zet power aan en check of het lampje van de hc-05 module per 2 seconde 1 keer knippert
 3. Upload het hc05 configuratie script wat in deze repo staat.

 5. Open de serial monitor, en zorg dat rechts onderin de baud rate op 38400 staat, en links daarvan staat op "both NL and CR"

 6. Test nu of de configuratie werkt, door "AT" in de serial monitor in te voeren. Als het goed is krijg je "OK" terug.
 7. Check if je op een 38400 baud rate zit, zo niet, gebruik command: "AT+UART=38400,0,0"

 8. Check nu of je hc-05 module in slave mode staat met "AT+ROLE?", als hij in slave configuratie staat, wordt er "+ROLE:0" gereturnt. (doordat dit de default configuration is.)
 9. Vraag nu het mac adres van je hc-05 module op met "AT+ADDR?". Schrijf op, of bewaar het mac adres wat je terug krijgt.


 **Master**.

 9. Houdt het knopje van de bluetooth module in, waar je de master van wilt maken.
 10. Zet power aan en check of het lampje van de hc-05 module per 2 seconde 1 keer knippert
 11. Haal de rx en tx kabels er uit, en upload een het glove.ino schema
 12. Stop de rx en tx kabels weer terug als het glove.ino schema is geupload.

 13. Open de serial monitor, en zorg dat rechts onderin de baud rate op 38400 staat, en links daarvan staat op "both NL and CR"

 14. Test nu of de configuratie werkt, door "AT" in de serial monitor in te voeren. Als het goed is krijg je "OK" terug.
 15. check if je op een 38400 baud rate zit, zo niet, gebruik command: "AT+UART=38400,0,0"
 16. typ nu in de serial monitor: "AT+ROLE=1". hiermee verander je de default waarde (slave) in een master.
 17. typ nu in de serial monitor: "AT+CMODE=0". hiermee zet je de verbinding modus naar een fixed adres.
 18. nu kan je de command: "AT+BIND=MACADDRESS" gebruiken". LET OP. voer ipv "MACADDRESS", het mac address in wat je bij stap 8 hebt opgeschreven. Ook moet je ipv de "-" tussen de mac adress gegevens kommas plaatsen.

 Nu zijn de master en slave modules geconfigureerd (alleen aan elkaar, omdat je de master specifiek aan het mac address van de slave hebt gekoppeld. Dit zorgt voor extra security. Mocht het je niets uitmaken, kan je de command: "AT+CMODE=1" gebruiken. De slave kan zich nu aan verschillende hc05 modules koppelen. maar dit gebruiken we voor nu even niet.)


