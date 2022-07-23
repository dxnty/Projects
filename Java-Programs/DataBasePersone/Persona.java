package com.dxnty.db.userregistration;

public class Persona {
    private String nome , cognome , regione , codiceID , numCell;

    // ~~~Costruttore~~~  //
    public Persona(String nome , String cognome , String codeID , String regione , String numCell )
    {
        setNome(nome);
        setCognome(cognome);
        setCodiceID(codeID);
        setRegione(regione);
        setNumCell(numCell);
    }

    // ~~~Costruttore senza parametri~~~ //
    public Persona() {}

    // Permette di avere in output i dati generali di Persona
    public void stampaGenPersona()
    {
        System.out.println("\n\t {Nome} : " + this.nome);
        System.out.println("\n\t {Cognome} : " + this.cognome);
        System.out.println("\n\t {RegioneDomicilio} : " + this.regione);
        System.out.println("\n\t {NumeroCellulare} : " + this.numCell);
    }

    // ~~~Get Method~~~ //
    public String getNome() {
        return nome;
    }

    public String getCognome() {
        return cognome;
    }

    public String getRegione() {
        return regione;
    }

    public String getCodiceID() {
        return codiceID;
    }

    public String getNumCell() {
        return numCell;
    }

    // ~~~Set Method~~~ //
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setCognome(String cognome) {
        this.cognome = cognome;
    }

    public void setRegione(String regione) {
        this.regione = regione;
    }

    public void setCodiceID(String codiceID) {
        this.codiceID = codiceID;
    }

    public void setNumCell(String numCell) {
        this.numCell = numCell;
    }

}  /* Fine classe */
