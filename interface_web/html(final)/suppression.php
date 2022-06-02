<!doctype hmtl>

<html>
  <head>
    <meta chearset="utf-8">
    <title>
      Projet Portail
    </title>
    <link href="../css/style.css" rel="stylesheet" type="text/css">
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <?php include "../login/secu2.php"?>
  </head>
  <body>

  <div class="content">
    <h1>Suppression</h1>
      <form class="" action="suppression.php" method="get">
	  <input type="nom" id="nom" name="nom" placeholder="Nom" required /><br></br>
	  <input type="prenom" id="prenom" name="prenom" placeholder="Prenom" required /><br></br>
    <p>Veuillez remplir ce formulaire pour ainsi supprimer la personne voulu.</p>
      <input type="submit" name="button" onclick="return confirm('Êtes-vous sûr de vouloir supprimer cet utilisateur ?');" value="Supprimer"></input>
    </form>

  </div>
  
<div class="sidenav">
<a href="../accueil/accueil.php"><h2>Accueil</h2></a>
  <a href="../inscription/inscription.php">Inscription</a>
  <a href="suppression.php">Suppression</a>
  <a href="../mail/mail.php">Envoi QR Code par mail</a>
  <a href="../login/logout.php">Déconnexion</a>
  <a id="lien_vieljeux" href="https://lycee-vieljeux.fr/"><IMG src="../images/logo-lycee-vieljeux-small.png" height="100" width="170"></IMG></a>
</div>
  <div class="logo_html">
  <a href="http://www.w3.org/html/logo/">
<img src="https://www.w3.org/html/logo/badge/html5-badge-h-css3.png" width="133" height="64" alt="HTML5 Powered with CSS3 / Styling" title="HTML5 Powered with CSS3 / Styling"></a>
  </div>

    <?php
  if($_GET['prenom']=="" or $_GET['nom']=="")
  {}
else{
	//id et mdp pour se connecter à la base de données
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
}
?>

</body>
</html>
