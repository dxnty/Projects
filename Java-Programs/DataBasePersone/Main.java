package com.dxnty.db.userregistration;

import java.util.Scanner;
import java.sql.*;

public class Main {

    static final String DB_URL = "jdbc:mariadb://localhost:3306/TestDB";

    //Credenziali db
    static final String USER = "dxnty";
    static final String PASS = "4152";

    public static void main(String[] args) {

        Persona pers[] = new Persona[10];
        Scanner sc = new Scanner(System.in);
        Connection conn = null;
        PreparedStatement stmp;
        ResultSet res;

        String nome = "" , cognome = "" , codeID = "" , regione = "" , numCell = "";
        int condSwitch , i = 0 , sizeArray = 0;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
        }catch(SQLException e) {
            System.out.println("\n\t [!] Errore Sql exception :: " + e);
            e.printStackTrace();
        }finally {
            System.out.println("\n\t [*] Connessione effettuata!\n");
        }

        printMenu();
        condSwitch = sc.nextInt(); // 1 -> print Persona from DB | 2 -> insert Persona in DB | 3 -> close the app

        switch(condSwitch)
        {
            case 1: //user wants to print all the persons in the db
                System.out.println("\n\t[] Stampa in corso delle Persone nel DB . . .\n");
                try {
                    assert conn != null;
                    stmp = conn.prepareStatement("SELECT * FROM Persona");
                    res = stmp.executeQuery();
                    while( res.next() )
                    {
                        pers[i] = new Persona();
                        pers[i].setNome(res.getString("Nome"));
                        pers[i].setCognome( res.getString("Cognome") );
                        pers[i].setRegione( res.getString("RegioneDomicilio") );
                        pers[i].setCodiceID( res.getString("CodiceID") );
                        pers[i].setNumCell( res.getString("NumCellulare") );

                        i++;
                        sizeArray++;
                    }
                }catch(SQLException e)
                {
                    System.out.println("\n\t[!] Errore :: " + e);
                    e.printStackTrace();
                }
                finally {
                    System.out.println("\n\t[*] Lettura dati effettuata con successo!\n");
                    for ( i = 0 ; i < sizeArray ; i++ )
                    {
                        System.out.println("[] Stampa Persone in corso . . .\n");
                        pers[i].stampaGenPersona(); //print the generic data of a 'Persona'
                    }
                }
                break;
            case 2: //user wants to insert a person in the db

                break;
            case 3: //user wants to close the app
                System.exit(0);
                break;

        }

    } //fine main

    public static void printMenu()
    {
        System.out.println("\n\t [] Stampa menu in corso  . . .");
        System.out.println("\n\t[1] Visualizza Persone nel DB");
        System.out.println("\n\t[2] Inserisci Persone nel DB");
        System.out.println("\n\t[3] Chiudi programma\n");
    }

} /* End of file */
