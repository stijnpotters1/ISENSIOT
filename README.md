# ISENSIOT-robot-arm


This is an arduino directory for the hand gesture controlled robot arm


## Bluetooth configuratie:
### Circuits
Gebruik tijdens de **configuratie** voor de arduino **uno** tijdelijk dit circuit. 
![Schermafbeelding 2023-12-11 174135](https://github.com/stijnpotters1/ISENSIOT/assets/93516547/87967cdd-b233-4746-8e47-df9660d04493)

Gebruik tijdens de **configuratie** voor de arduino **nano** tijdelijk dit circuit. 
![Schermafbeelding 2023-12-11 172838](https://github.com/stijnpotters1/ISENSIOT/assets/93516547/e2e2eafd-623f-40bc-a3a4-3b2a9f872e34)



 ### Slave (uno):

 1. Houdt het knopje van de bluetooth module in, waar je de slave van wilt maken (in ons geval de uno).
 2. Zet power aan en check of het lampje van de hc-05 module per 2 seconde 1 keer knippert
 3. **upload** het **HC05-CONFIGURATION** schema
 5. Open de serial monitor, en zorg dat rechts onderin de baud rate op 38400 staat, en links daarvan staat op "both NL and CR"
 5. Test nu of de configuratie werkt, door "**AT**" in de serial monitor in te voeren. Als het goed is krijg je "**OK**" terug.
 6. Check of je op een 38400 baud rate zit met de command: "**AT+UART?**", zo niet, gebruik command: "**AT+UART=38400,0,0**".
 7. Check nu of je hc-05 module in slave mode staat met "**AT+ROLE?**", als het goed is wordt er "**+ROLE:0**" gereturnt. (dat komt doordat dit de 
    default configuration is.)
 8. Vraag nu het mac adres van je HC05 module op met "**AT+ADDR?**". Schrijf op, of bewaar het mac adres wat je terug krijgt.
 9. Verander nu je circuit naar deze opstelling. (dit is het vaste circuit wat we gebruiken voor de robot arm):
     ![Schermafbeelding 2023-12-11 174157](https://github.com/stijnpotters1/ISENSIOT/assets/93516547/3e38f85d-5b93-4e69-ba83-9867a2c7187a)



 ### Master (Nano).

 10. Houdt het knopje van de bluetooth module in, waar je de master van wilt maken (in ons geval de nano).
 11. Zet power aan en check of het lampje van de hc-05 module per 2 seconde 1 keer knippert
 12. **upload** het **HC05-CONFIGURATION** schema 
 13. Open de serial monitor, en zorg dat rechts onderin de baud rate op 38400 staat, en links daarvan staat op "both NL and CR"
 14. Test nu of de configuratie werkt, door "**AT**" in de serial monitor in te voeren. Als het goed is krijg je "OK" terug.
 15. Check of je op een 38400 baud rate zit met de command: "**AT+UART?**", zo niet, gebruik command: "**AT+UART=38400,0,0**".
 16. Typ nu in de serial monitor: "**AT+ROLE=1**". hiermee verander je de default waarde (slave) naar een master.
 17. Typ nu in de serial monitor: "**AT+CMODE=0**". hiermee zet je de verbinding modus naar een adres op fixed.
 18. Nu kan je de command: "**AT+BIND=XXXX,XX,XXXXXX**" gebruiken". **LET OP**. voer ipv "XXXX,XX,XXXXXX", het mac address in wat je bij **stap 8** hebt 
     opgeschreven. Ook moet je er op letten dat je **kommas** plaatst tussen de characters ipv een "-".
 19. Nu zijn de master en slave modules geconfigureerd. (alleen aan elkaar, omdat je de master specifiek aan het mac address van de slave hebt gekoppeld. Dit 
     zorgt voor extra security. Mocht het je niets uitmaken, kan je de command: "AT+CMODE=1" gebruiken. De slave kan zich nu aan verschillende HC05 master  
     modules koppelen. maar voor nu gebruiken we dit even niet).
 20. Verander nu je circuit naar deze opstelling. (dit is het vaste circuit wat we gebruiken voor de handschoen)
     ![Schermafbeelding 2023-12-11 173013](https://github.com/stijnpotters1/ISENSIOT/assets/93516547/69ea4581-255f-49f4-b52d-9c8a225db225)


 ### Algemeen:
 
 21. Als je nu de twee HC05 modules aan stroom zet. gaan ze nu in de derde stand. Dit is de gekoppelde stand. Dit kun je herkennen doordat de lampjes op beide 
     modules, nu twee keer synchrone gaan knipperen. 
 22. upload op de **Arduino Nano** de **Glove.ino** code.
 23. upload op de **Arduino Uno** de **Robotarm.uno** code.

### Voltooid!
 24. als het goed is heb je nu een werkende bluetooth connectie. (Dit kan je testen door te checken of de messages van de arduino nano in de seriele monitor van 
     de arduino uno binnen komen.


## Final version robot arm en handschoen circuit diagrammen:
### Robotarm
![image](https://github.com/stijnpotters1/ISENSIOT/assets/93516547/7bed86b9-cfd7-4ec8-887b-ab1e5679e73f)

### Handschoen
![image](https://github.com/stijnpotters1/ISENSIOT/assets/93516547/8a376df3-5afa-427f-9601-b21c8182507d)



