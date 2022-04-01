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
    <h1>Inscription</h1>
      <form class="" action="inscription.php" method="get">
	  <input type="nom" id="nom" name="nom" placeholder="Nom" required /><br></br>
	  <input type="prenom" id="prenom" name="prenom" placeholder="Prenom" required /><br></br>
	  <input type="adresse_mail" id="adresse_mail" name="adresse_mail" placeholder="Adresse Mail" required /><br></br>
    <br>Veuillez remplir ce formulaire pour ainsi inscrire la personne voulu.</br><p></p>
      <input type="submit" name="button"></input>
    </form>

  </div>
  
<div class="sidenav">
  <a href="index.html"><h2>Accueil</h2></a>
  <a href="inscription.html">Inscription</a>
  <a href="desinscription.html">Desinscription</a>
  <a href="mail.html">Envoi QR Code par mail</a>
  <a id="lien_vieljeux" href="https://lycee-vieljeux.fr/"><IMG src="logo-lycee-vieljeux-small.png" height="100" width="170"></IMG></a>
</div>

</div>
<div class="content">
  <div id="logo_html">
  <a href="http://www.w3.org/html/logo/">
<img src="https://www.w3.org/html/logo/badge/html5-badge-h-css3.png" width="133" height="64" alt="HTML5 Powered with CSS3 / Styling" title="HTML5 Powered with CSS3 / Styling"></a>
  </div>

	<?php
		//id et mdp pour se connecter à la base de données
            $servname = 'localhost';
            $dbname = 'Portail';
            $user = 'portail';
            $pass = 'portail';
            $nom = $_GET['nom'];
            $prenom = $_GET['prenom'];
	    $adresse_mail = $_GET['adresse_mail'];
				//connexion à la base de donnée
                $dbco = new PDO("mysql:host=$servname;dbname=$dbname", $user, $pass);
                $dbco->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
                //préparation de la requête sql
                $sql = "INSERT INTO Personnel(nom,prenom,QR,adresse_mail)
                        VALUES('$nom','$prenom',SUBSTRING(MD5(RAND()) FROM 1 FOR 8), '$adresse_mail')";
                //exécution de la requête sql
                $dbco->exec($sql);
                echo '<script>alert("Entrée ajoutée dans la table")</script>';
        ?>
  </body>
</html>
