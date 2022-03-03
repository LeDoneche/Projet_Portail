<html>
    <head>
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/webrtc-adapter/3.3.3/adapter.min.js"></script>
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/vue/2.1.10/vue.min.js"></script>
        <link rel="stylesheet" type="text/css" href="font.css">
    </head>
    
    <body>
        <div class="container">
            <div class="ligne">
                <div class="un">
                    <video id="preview" width="50%"></video>
                </div>
                <div class="un">
                    <label>QR Code</label>
                    <imput type="text" name="text" id="text" readonyy="" placeholder="scan QR Code" class="form-controle"></imput>  
                </div>
            </div>
        </div>
        
       <script src="vglnk" href="https://rawgit.com/schmich/instascan-builds/master/instascan.min.js" rel="nofollow"></script>
        <script type="text/javascript">
            let scanner = new Instascan.Scanner({ video: document.getElementById('preview'), scanPeriod: 1, mirror: false });
            Instascan.Camera.getCameras().then(function(cameras){
                if ( cameras.length > 0){
                    scanner.start(cameras[0]);
                
            } 
                else {
                    alert(' Pas de caméras trouvé ');
                }
            }). catch (function(e) {
                 console.error(e);
            });
            
            scanner.addListener('scan', function(c)){
                document.getDocumentById('text').value-c;
                document.forms[0].submit();    
            });
        </script>
    </body>
</html>