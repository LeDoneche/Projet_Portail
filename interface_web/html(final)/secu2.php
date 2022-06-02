<?php
    session_start();
    if (!isset($_SESSION['sid'])) {
      header("location: ../login/acces_interdit.php");
      exit;
}
session_write_close(); // fermeture de la session pour éviter les warning si t'en ré-ouvres une dans ta page.
?> 