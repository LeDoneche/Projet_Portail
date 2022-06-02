<!doctype HTML>
<html lang="fr">
  <head>
    <title>
      Projet Portail
    </title>
    <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href="../css/style.css" rel="stylesheet" type="text/css">
    <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">

    <?php include "../login/secu2.php"?>
  </head>
  <body>

<div class="sidenav">
  <a href="accueil.php"><h2>Accueil</h2></a>
  <a href="../inscription/inscription.php">Inscription</a>
  <a href="../suppression/suppression.php">Suppression</a>
  <a href="../mail/mail.php">Envoi QR Code par mail</a>
  <a id="deco" href="../login/logout.php">Déconnexion</a>
  <a id="lien_vieljeux" href="https://lycee-vieljeux.fr/"><IMG src="../images/logo-lycee-vieljeux-small.png" height="100" width="170" alt="logo_vieljeux"></a>
</div>

<div class="content">
  
  <h1>Projet Portail</h1>
  <p>Ceci est l'interface web pour gérer les utlisateurs pouvant ouvrir le portail grâce à leurs QR Code.</p>
  <p>Les différentes fonctionnalités disponibles sont à gauche.</p><br>
  <p>L'Inscription : permet d'inscrire un nouvel utlisateur pour pouvoir ensuite ouvrir le portail grâce au QR Code.</p>
  <p>La Désinscription : permet de supprimer de la base de donnée un utilisateur, donc il ne pourra plus ouvrir le portail avec son QR Code.</p>
  <p>L'Envoi QR Code : permet d'envoyer un mail avec le QR Code en pièce jointe si l'utilisateur est bien inscris.</p>
  
  <table>
  <?php

      echo "<tr><th>Nom</th><th>Prénom</th><th>Email</th></tr>";
    	    //id et mdp pour se connecter à la base de données
            $servname = 'localhost';
            $dbname = 'Portail';
            $user = 'portail';
            $pass = 'portail';
		//connexion à la base de donnée
                $conn = new mysqli($servname, $user, $pass, $dbname);
                // Check connection
	                if ($conn->connect_error) {
	                    die("Connection failed: " . $conn->connect_error);
	                }

                $sql = "SELECT `nom`, `prenom`, `adresse_mail` FROM `Personnel`";
                //exécution de la requête sql
                $result = $conn->query($sql);

                if ($result->num_rows > 0) {
                  // output data of each row
                  while($row = mysqli_fetch_assoc($result)) {
                    printf ("<tr><td>%s</td><td>%s</td><td>%s</td></tr>", $row["nom"], $row["prenom"], $row["adresse_mail"]);
                  }
                } else {
                  echo "0 results";
                }

  ?>
  </table>
</div>
  <div class="logo_html">
  <a href="http://www.w3.org/html/logo/">
<img src="https://www.w3.org/html/logo/badge/html5-badge-h-css3.png" width="133" height="64" alt="HTML5 Powered with CSS3 / Styling" title="HTML5 Powered with CSS3 / Styling"></a>
</div>

</body>
</html>
