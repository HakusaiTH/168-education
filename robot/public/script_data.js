//const audio = new Audio("/static/audio/พาราเซตามอล.mp3");
const btn_a = document.getElementById("btn_a");
r_sta = 1;
document.getElementById("r").addEventListener('click',()=>{
    r_sta ++;
    if((r_sta % 2) == 0){
        audio.play();
        btn_a.src = "/static/images/speker.png"
    }
    else{
        audio.pause();audio.currentTime = 0;
        btn_a.src = "/static/images/speke_nr.png"
    }
})

document.getElementById("g").addEventListener('click',()=>{
    document.getElementById("num_n").style.display = "flex";
    document.getElementById("container").style.display = "none";
})

const firebaseConfig = {
    apiKey: "AIzaSyAfm-wnbuOAVQESBQASW6iyULVu6-Epr3M",
    authDomain: "my-robot-9fdff.firebaseapp.com",
    databaseURL: "https://my-robot-9fdff-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "my-robot-9fdff",
    storageBucket: "my-robot-9fdff.appspot.com",
    messagingSenderId: "989347540267",
    appId: "1:989347540267:web:cfbfa6664cc4e5d2f0e96e",
    measurementId: "G-LXEWXSLQC5"
};
firebase.initializeApp(firebaseConfig);

$(document).ready(function(){
    var database = firebase.database();

    document.getElementById("g").addEventListener('click',()=>{
        var firebaseRef = firebase.database().ref().child("Status");
        firebaseRef.set(d_);
    })
});

console.log("pass");  