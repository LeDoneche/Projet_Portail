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
    <h1>Desinscription</h1>
      <form class="" action="desinscription.php" method="get">
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

</div>
<div class="content">
  <div id="logo_html">
  <a href="http://www.w3.org/html/logo/">
<img src="https://www.w3.org/html/logo/badge/html5-badge-h-css3.png" width="133" height="64" alt="HTML5 Powered with CSS3 / Styling" title="HTML5 Powered with CSS3 / Styling"></a>
  </div>

<?php
    $host = 'localhost';
    $username = 'portail';
    $password = 'portail';
    $db = 'Portail';
    $nom = $_GET['nom'];
    $prenom = $_GET['prenom'];


//Créez l'objet PDO
$pdo = new PDO("mysql:host=$host;dbname=$db", $username, $password);

//Suppression d'une ligne à l'aide d'une instruction préparée
$sql = "DELETE FROM Personnel WHERE nom = '$nom' AND prenom = '$prenom';";

//Préparez notre déclaration DELETE
$stmt = $pdo->prepare($sql);

//Exécuter notre instruction DELETE
$res = $stmt->execute();

echo '<script>alert("Entrée supprimée dans la table")</script>';

?>

</body>
</html>
