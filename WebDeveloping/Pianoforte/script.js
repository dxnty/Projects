const developerName = "Dxnty"; //name wont change
console.log("Script made by " + developerName);

const buttonKeys = document.querySelectorAll('.key');
const notes = {
    do: '01-do.mp3',
    dodiesis: '02-dodiesis.mp3',
    re: '03-re.mp3',
    rediesis: '04-rediesis.mp3',
    mi: '05-mi.mp3',
    fa: '06-fa.mp3',
    fadiesis: '07-fadiesis.mp3',
    sol: '08-sol.mp3',
    soldiesis: '09-soldiesis.mp3',
    la: '10-la.mp3',
    ladiesis: '11-ladiesis.mp3',
    si: '12-si.mp3'
}

/* dichiarazioni e sviluppo funzioni */
function playSound(key) {
    const audioElem = new Audio();
    /* const note = notes[key]; || = notes.key */
    audioElem.src = 'sounds/' + notes[key]; //key = node.id
    audioElem.play();
}   


buttonKeys.forEach(function(node) {
    node.addEventListener('touchend' , function() {
        playSound( node.id );
    });
});






