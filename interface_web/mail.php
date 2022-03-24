<!doctype hmtl>

<html>
  <head>
    <meta chearset="utf-8">
    <title>
      Projet Portail
    </title>
    <link href="/css/style.css" rel="stylesheet" type="text/css">
  </head>
  <body>

  <div class="content">
    <h1>Envoi QR Code</h1>
      <form class="" action="mail.php" method="get">
	  <input type="nom" id="nom" name="nom" placeholder="Nom" required /><br></br>
	  <input type="prenom" id="prenom" name="prenom" placeholder="Prenom" required /><br></br>
    
      <input type="submit" name="button"></input>
    </form>

  </div>
  
<div class="sidenav">
  <a href="index.html"><h2>Accueil</h2></a>
  <a href="inscription.html">Inscription</a>
  <a href="desinscription.html">Desinscription</a>
  <a href="mail.html">L'Envoi QR Code par mail</a>
  <a id="lien_vieljeux" href="https://lycee-vieljeux.fr/"><IMG src="logo-lycee-vieljeux-small.png" height="100" width="170"></IMG></a>
</div>

<div class="content">
<div id="logo_html">
  <a href="http://www.w3.org/html/logo/">
<img src="https://www.w3.org/html/logo/badge/html5-badge-h-css3.png" width="133" height="64" alt="HTML5 Powered with CSS3 / Styling" title="HTML5 Powered with CSS3 / Styling"></a>
  </div>
</div>

<?php

	include('phpqrcode/qrlib.php');
	
	$servername = "localhost";
	$username = "portail";
	$password = "portail";
	$dbname = "Portail";
	$nom = $_GET['nom'];
	$prenom = $_GET['prenom'];

	// Create connection
	  $conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	  if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	  }

	  $sql = "SELECT adresse_mail FROM Personnel WHERE nom = '$nom' AND prenom = '$prenom'";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
    $data = $row["adresse_mail"];
  }
} else {
  echo "0 results";
}

$conn->close();

$tempDir = "tmp/";
$fileName = "QRCode_"."$nom"."_"."$prenom.png";
$pngAbsoluteFilePath = $tempDir.$fileName;
$urlRelativeFilePath = $tempDir.$fileName;

$mail = "$data"; // Déclaration de l'adresse de destination.
if (!preg_match("#^[a-z0-9._-]+@(hotmail|live|msn).[a-z]{2,4}$#", $mail)) // On filtre les serveurs qui présentent des bogues.
{
    $passage_ligne = "\r\n";
}
else
{
    $passage_ligne = "\n";
}
//=====Déclaration des messages au format texte et au format HTML.
$message_txt = "Voici le QR Code";
$message_html = "<html><head></head><body>Voici le QR Code</body></html>";
//==========
  
//=====Lecture et mise en forme de la pièce jointe.
$fichier   = fopen("tmp/QRCode_$nom"."_"."$prenom.png", "r");
$attachement = fread($fichier, filesize("tmp/QRCode_$nom"."_"."$prenom.png"));
$attachement = chunk_split(base64_encode($attachement));
fclose($fichier);
//==========
  
//=====Création de la boundary.
$boundary = "-----=".md5(rand());
$boundary_alt = "-----=".md5(rand());
//==========
  
//=====Définition du sujet.
$sujet = "QR Code";
//=========
  
//=====Création du header de l'e-mail.
$header = "From: \"Portail\"<portail@portail.fr>".$passage_ligne;
$header.= "Reply-to: \"Portail\"<portail@portail.fr>".$passage_ligne;
$header.= "MIME-Version: 1.0".$passage_ligne;
$header.= "Content-Type: multipart/mixed;".$passage_ligne." boundary=\"$boundary\"".$passage_ligne;
//==========
  
//=====Création du message.
$message = $passage_ligne."--".$boundary.$passage_ligne;
$message.= "Content-Type: multipart/alternative;".$passage_ligne." boundary=\"$boundary_alt\"".$passage_ligne;
$message.= $passage_ligne."--".$boundary_alt.$passage_ligne;
//=====Ajout du message au format texte.
$message.= "Content-Type: text/plain; charset=\"ISO-8859-1\"".$passage_ligne;
$message.= "Content-Transfer-Encoding: 8bit".$passage_ligne;
$message.= $passage_ligne.$message_txt.$passage_ligne;
//==========
  
$message.= $passage_ligne."--".$boundary_alt.$passage_ligne;
  
//=====Ajout du message au format HTML.
$message.= "Content-Type: text/html; charset=\"ISO-8859-1\"".$passage_ligne;
$message.= "Content-Transfer-Encoding: 8bit".$passage_ligne;
$message.= $passage_ligne.$message_html.$passage_ligne;
//==========
  
//=====On ferme la boundary alternative.
$message.= $passage_ligne."--".$boundary_alt."--".$passage_ligne;
//==========
  
  
  
$message.= $passage_ligne."--".$boundary.$passage_ligne;
  
//=====Ajout de la pièce jointe.
$message.= "Content-Type: image/png; name=\"image.png\"".$passage_ligne;
$message.= "Content-Transfer-Encoding: base64".$passage_ligne;
$message.= "Content-Disposition: attachment; filename=\"image.png\"".$passage_ligne;
$message.= $passage_ligne.$attachement.$passage_ligne.$passage_ligne;
$message.= $passage_ligne."--".$boundary."--".$passage_ligne;
//==========
//=====Envoi de l'e-mail.
mail($mail,$sujet,$message,$header);
  
//==========

?>
</body>
</html>
