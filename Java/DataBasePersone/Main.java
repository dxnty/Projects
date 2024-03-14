package com.dxnty.db.userregistration;
import java.util.Scanner;
import java.sql.*;

public class Main {

    static final String DB_URL = "jdbc:mariadb://localhost:3306/TestDB";

    //DB credentials
    static final String USER = "dxnty" , PASS = "4152";

    public static void main(String[] args) {

        Persona[] pers = new Persona[10]; //create an array of 10 null Persona obj
        Scanner sc = new Scanner(System.in); //scanner's initialization
        Connection conn = null; //initialize the Connection variable
        PreparedStatement stmp; //will allow the user to interrogate the database
        ResultSet res; //will contain the results of the sql query

        //variables to construct the Persona's obj
        String nome = "", cognome = "", codeID = "", regione = "", numCell = "";

        int condSwitch = 0 , i = 0  , t = 1 , j = 0 , sizeArray = 0 , numObj = 0;
        /*
            condSwitch -> will contain the answer of the user to the menu's choices [ lines : 46 - 49 ]
            i , t , j ---> variables used in for loops [ lines : 74 - 75 | 90 | 103 ]
            sizeArray -> allow me to differentiate the array's size from the array's length ( ask ,or search, for further explanation ) [ lines : 66 | 74]
            numObj -> will contain the number of Persona's obj that the user want to insert into the db [ line : 85 - 90 ]
         */
        boolean condWhile = true;

        // Execute the connection to the database
        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
        } catch (SQLException e) {
            System.out.println("\n\t [!] Errore Sql exception :: " + e);
            e.printStackTrace();
        } finally {
            System.out.println("\n\t [*] Connessione effettuata!\n");
        }

        // Menu phase
        System.out.println("\n\n\n\t\t [] Stampa menu in corso  . . .\n");
        while ( condWhile ) {
            System.out.println("\n\n");
            printMenu();
            condSwitch = sc.nextInt(); // 1 -> print Persona from DB | 2 -> insert Persona in DB | 3 -> close the app

            switch (condSwitch) {
                case 1 ->
                { //user wants to print all the persons in the db
                    System.out.println("\n\t[] Stampa in corso delle Persone nel DB . . .\n");
                    try {
                        assert conn != null;
                        stmp = conn.prepareStatement("SELECT * FROM Persona");
                        res = stmp.executeQuery();
                        while (res.next()) {
                            pers[i] = new Persona();
                            pers[i].setNome(res.getString("Nome"));
                            pers[i].setCognome(res.getString("Cognome"));
                            pers[i].setRegione(res.getString("RegioneDomicilio"));
                            pers[i].setCodiceID(res.getString("CodiceID"));
                            pers[i].setNumCell(res.getString("NumCellulare"));

                            i++;
                            sizeArray++;
                        }
                    } catch (SQLException e) {
                        System.out.println("\n\t[!] Errore :: " + e);
                        e.printStackTrace();
                    } finally {
                        System.out.println("\n\t[*] Lettura dati effettuata con successo!\n");
                        System.out.println("[] Stampa Persone in corso . . .\n");
                        for (i = 0; i < sizeArray; i++) {
                            System.out.println("\n\t [" + t + "]");
                            pers[i].stampaGenPersona(); //print the generic data of a 'Persona'
                            t++;
                        }
                    }
                }

                case 2 ->
                { //user wants to insert a person in the db
                    System.out.println("\n\tQuante persone vuoi inserire nel database? : ");
                    numObj = sc.nextInt();
                    assert numObj >= 0;
                    if (numObj == 0) {
                        System.out.println("\n\tOkay!\n");
                    } else {
                        for ( j = 0 ; j < numObj ; j++ )
                        {
                            System.out.println("\n\t [Nome] :  ");
                            nome = sc.next();
                            System.out.println("\n\t [Cognome] : ");
                            cognome = sc.next();
                            System.out.println("\n\t [Regione] : ");
                            regione = sc.next();
                            System.out.println("\n\t [Codice ID] : ");
                            codeID = sc.next();
                            System.out.println("\n\t [Numero Cellulare] : ");
                            numCell = sc.next();

                            pers[j] = new Persona(nome , cognome , codeID , regione , numCell );

                            try {
                                assert conn != null;
                                stmp = conn.prepareStatement
                                        (
                                    "insert into `Persona`(`Nome`, `Cognome`, `CodiceID`, `NumCellulare`, `RegioneDomicilio`) values('" + nome +"' , '" + cognome +"' , '" + codeID + "' , '" + numCell +"' , '"+regione+"');"
                                        );
                                stmp.executeQuery();
                            }catch (SQLException e) {
                                System.out.println("\n\t[!] Errore :: "+ e);
                            }

                        }/* /for */
                    }/*  /else */
                }

                case 3 ->
                { //user wants to close the app
                    condWhile = false;
                    System.exit(0);
                }

            } //end switch
        } //end while

    } //end function main

    public static void printMenu()
    {
        System.out.println("\n\t[1] Visualizza Persone nel DB");
        System.out.println("\n\t[2] Inserisci Persone nel DB");
        System.out.println("\n\t[3] Chiudi programma\n");
    }

} //end Class Main
