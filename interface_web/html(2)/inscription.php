<!doctype HTML>
<html lang="fr">
  <head>
    <meta charset="utf-8">
    <title>
      Projet Portail
    </title>
    <link href="../css/style.css" rel="stylesheet" type="text/css">
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
    <?php include "../login/secu2.php"?>
    <?php ?>
  </head>
  <body>

  <div class="content">
    <h1>Inscription</h1>
      <form class="" action="inscription.php" method="get">
	
	  <input id="nom" name="nom" placeholder="Nom" required /><br><br>
	  <input id="prenom" name="prenom" placeholder="Prenom" required /><br><br>
	  <input id="adresse_mail" name="adresse_mail" placeholder="Adresse Mail" required /><br><br>
    <p>Veuillez remplir ce formulaire pour ainsi inscrire la personne voulu.</p>
      <input type="submit" name="button">
    </form>

  </div>
  
<div class="sidenav">
<a href="../accueil/accueil.php"><h2>Accueil</h2></a>
  <a href="inscription.php">Inscription</a>
  <a href="../suppression/suppression.php">Suppression</a>
  <a href="../mail/mail.php">Envoi QR Code par mail</a>
  <a href="../login/logout.php">Déconnexion</a>
  <a id="lien_vieljeux" href="https://lycee-vieljeux.fr/"><IMG src="../images/logo-lycee-vieljeux-small.png" height="100" width="170" alt="logo_vieljeux"></a>
  
</div>
  <div class="logo_html">
  <a href="http://www.w3.org/html/logo/">
<img src="https://www.w3.org/html/logo/badge/html5-badge-h-css3.png" width="133" height="64" alt="HTML5 Powered with CSS3 / Styling" title="HTML5 Powered with CSS3 / Styling"></a>
</div>

	<?php

  if($_GET['prenom']=="" or $_GET['nom']=="" or $_GET['adresse_mail']=="")
  {}
else{
	    //id et mdp pour se connecter à la base de données
            $servname = 'localhost';
            $dbname = 'Portail';
            $user = 'portail';
            $pass = 'portail';
            $nom = $_GET['nom'];
            $prenom = $_GET['prenom'];
	        $adresse_mail = $_GET['adresse_mail'];
		//connexion à la base de donnée
                $conn = new mysqli($servname, $user, $pass, $dbname);
                // Check connection
	                if ($conn->connect_error) {
	                    die("Connection failed: " . $conn->connect_error);
	                }

                $sql = "SELECT `nom`, `prenom` FROM `Personnel` WHERE nom='$nom' AND prenom='$prenom'";
                //exécution de la requête sql
                $result = $conn->query($sql);

                if ($result->num_rows > 0) {
                  // output data of each row
                  while($row = $result->fetch_assoc()) {
                    $data = $row["nom"];
                    $data2 = $row["prenom"];
                  }
                } else {
                  echo "0 results";
                }
                
                if($data!==$nom or $data2!==$prenom){

                $sql2 = "INSERT INTO Personnel(nom,prenom,QR,adresse_mail)
                        VALUES('$nom','$prenom',SUBSTRING(MD5(RAND()) FROM 1 FOR 8), '$adresse_mail')";
                //exécution de la requête sql
                $conn->query($sql2);
                echo '<script>alert("Entrée ajoutée dans la table")</script>';
                }
                else{
                    echo '<script>alert("Erreur la personne est déjà dans la table")</script>';

                }
                $conn->close();
}
        ?>
  </body>
</html>
