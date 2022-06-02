<?php

if($_GET['username']=="" or $_GET['pass']=="")
  {}
else{

$uid = $_GET['username'];
$pw = $_GET['pass'];
 
if($uid == 'admin' and $pw == 'admin')
{    
    session_start();
    $_SESSION['sid']=session_id();
    header("location: ../accueil/accueil.php");
}
elseif($uid !== 'admin' or $pw !== 'admin'){
    echo "<p>Le nom d'utilisateur ou le mot de passe est erroné</p>";
}
}

?>