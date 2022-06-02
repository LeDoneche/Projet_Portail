<!DOCTYPE html>
<html lang="fr">
<head>
	<title>Accès parking</title>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
<!--===============================================================================================-->	
	<link rel="icon" type="image/png" href="images/icons/favicon.ico"/>
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="css/fonts/font-awesome-4.7.0/css/font-awesome.min.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="css/fonts/Linearicons-Free-v1.0.0/icon-font.min.css">
<!--===============================================================================================-->
	<link rel="stylesheet" type="text/css" href="css/util.css">
	<link rel="stylesheet" type="text/css" href="css/main.css">
<!--===============================================================================================-->
</head>
<body>
	
	<div class="limiter">
		<div class="container-login100">
			<div class="wrap-login100 p-t-50 p-b-90">
				<form class="login100-form validate-form flex-sb flex-w" method="get" action="index.php">
					<span class="login100-form-title p-b-51">
						Accès Parking
					</span>
					<div class="wrap-input100 validate-input m-b-16">
						<input class="input100" type="text" name="username" placeholder="Nom d'utilisateur" required>
						<span class="focus-input100"></span>
					</div>
					
					<div class="wrap-input100 validate-input m-b-16">
						<input class="input100" type="password" name="pass" placeholder="Mot de passe" required>
						<span class="focus-input100"></span>
					</div>
					
					<div class="flex-sb-m w-full p-t-3 p-b-24">
						<div>

                        <?php include "login/login.php"; ?>
                            
						</div>
                        
					</div>
                   
					    <div class="container-login100-form-btn m-t-17">
						    <input name="button" class="login100-form-btn" type="submit" value="Se connecter">
					    </div>
						
                    </form>
			</div>
		</div>
	</div>

	<div id="dropDownSelect1"></div>

</body>
</html>