const developerName = "Dxnty"; //name wont change
console.log("Script made by " + developerName);


/* dichiarazioni e sviluppo funzioni */
function playSound() {
    console.log("ciao mondo");
}




const buttonWhite = document.getElementById("key-whiteONE");
buttonWhite.addEventListener( "touchend", playSound() ); //quando premeremo il bottone verrà eseguita la funzione playSound() || solo alla fine "touchend"





