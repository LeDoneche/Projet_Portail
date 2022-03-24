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
  <script src="https://cdn.rawgit.com/davidshimjs/qrcodejs/gh-pages/qrcode.min.js"></script>

  <div class="form">
    <h1>Generateur QR Code</h1>
      <form class="" action="leqrcode.php" method="post">
	  <input type="nom" id="nom" name="nom" placeholder="Nom" required /><br></br>
	  <input type="prenom" id="prenom" name="prenom" placeholder="Prenom" required /><br></br>
    
      <button type="submit" name="button">Envoyer</button>
    </form>

  </div>

<?php
	include('phpqrcode/qrlib.php');
	$servername = "127.0.0.1";
	$username = "portail";
	$password = "portail";
	$dbname = "Portail";
	$nom = $_POST['nom'];
	$prenom = $_POST['prenom'];

	// Create connection
	  $conn = new mysqli($servername, $username, $password, $dbname);
	// Check connection
	  if ($conn->connect_error) {
	    die("Connection failed: " . $conn->connect_error);
	  }

	  $sql = "SELECT keyPswd FROM Personnel WHERE nom = '$nom' AND prenom = '$prenom'";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
    $data = $row["keyPswd"];
  }
} else {
  echo "0 results";
}

$conn->close();

$tempDir = "tmp/";
$fileName = "QRCode_"."$nom"."_"."$prenom.png";
$pngAbsoluteFilePath = $tempDir.$fileName;
$urlRelativeFilePath = $tempDir.$fileName;

    if (!file_exists($pngAbsoluteFilePath)) {
        QRcode::png($data, $pngAbsoluteFilePath);
        echo 'File generated!';
        echo '<hr />';
    } else {
        echo 'File already generated!';
        echo '<hr />';
    }

/*
// how to save PNG codes to server
    include('phpqrcode/qrlib.php');
    $tempDir = "tmp/";
    

    
    // we need to generate filename somehow, 
    // with md5 or with database ID used to obtains $codeContents...
    $fileName = '005_file_'.md5($data).'.png';
    
    $pngAbsoluteFilePath = $tempDir.$fileName;
    $urlRelativeFilePath = $tempDir.$fileName;
    
    // generating
    if (!file_exists($pngAbsoluteFilePath)) {
        QRcode::png($data, $pngAbsoluteFilePath);
        echo 'File generated!';
        echo '<hr />';
    } else {
        echo 'File already generated!';
        echo '<hr />';
    }
    
    echo 'Server PNG File: '.$pngAbsoluteFilePath;
    echo '<hr />';
    
    // displaying
    echo '<img src="'.$urlRelativeFilePath.'" />'; */
?>
    </body>
</html>
