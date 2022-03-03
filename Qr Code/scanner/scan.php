<html>
    <head>
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/webrtc-adapter/3.3.3/adapter.min.js"></script>
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/vue/2.1.10/vue.min.js"></script>
        <script type="text/javascript" src="https://rawgit.com/schmich/instascan-builds/master/instascan.min.js"></script>
        <link rel="stylesheet" type="text/css" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    </head>
    
    <body>
        <div class="container">
                <div class="un">
                    <video id="cam" width="10%" controls autoplay></video>
                </div>
                <div class="deux">
                    <label>Code :</label>
                    <input type="text" name="text" id="text" readonyy="" placeholder="IMAT" class="form-control"></input>  
                </div>
        </div>
        
       
        <script type="text/javascript">
            let scanner = new Instascan.Scanner({ video: document.getElementById('cam'), scanPeriod: 1, mirror: false });
            Instascan.Camera.getCameras().then(function(cameras){
                if ( cameras.length > 0){
                    scanner.start(cameras[0]);     
            }  else {
                    alert(' Pas de camera ');
                }
            }). catch (function(e) {
                 console.error(e);
            });
            
            scanner.addListener('scan', function(c){
                document.getElementById('text').value=c;
                document.forms[0].submit();    
            });
        </script>
    </body>
</html>