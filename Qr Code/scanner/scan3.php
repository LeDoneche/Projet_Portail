    <head>
        
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/webrtc-adapter/3.3.3/adapter.min.js"></script>
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/vue/2.1.10/vue.min.js"></script>
        <script type="text/javascript" src="https://rawgit.com/schmich/instascan-builds/master/instascan.min.js"></script>
		<link rel="stylesheet" rel="preload" as="style" onload="this.rel='stylesheet';this.onload=null" href="https://fonts.googleapis.com/css?family=Roboto:300,300italic,700,700italic">
		<link rel="stylesheet" rel="preload" as="style" onload="this.rel='stylesheet';this.onload=null" href="https://unpkg.com/normalize.css@8.0.0/normalize.css">
		<link rel="stylesheet" rel="preload" as="style" onload="this.rel='stylesheet';this.onload=null" href="https://unpkg.com/milligram@1.3.0/dist/milligram.min.css">
        
        <link rel="stylesheet" type="text/css" src="">
    </head>
    
    <body onload='auto_refresh()'>
          
          


        <section class="container" id="demo-content">
            <div>
                <a class="button" id="decodeButton">Decode</a>
            </div>

            <div>
                <img id="img" src="http://172.20.233.38/oneshotimage1?" style="border: 1px solid gray"></img>
            </div>

            <label>Result:</label>
            <pre><code id="result"></code></pre>
        </section>
    
     <script type="text/javascript" src="https://unpkg.com/@zxing/library@latest"></script>
    <script type="text/javascript">
        window.addEventListener('load', function () {
            const codeReader = new ZXing.BrowserQRCodeReader()
            console.log('ZXing code reader initialized')

            document.getElementById('decodeButton').addEventListener('click', () => {
                const img = document.getElementById('img')
                codeReader.decodeFromImage(img).then((result) => {
                    console.log(result)
                    document.getElementById('result').textContent = result.text
                }).catch((err) => {
                    console.error(err)
                    document.getElementById('result').textContent = err
                })
                console.log(`Started decode for image from ${img.src}`)
            })

        })
    </script>
  
        <script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jquery/1.3.0/jquery.min.js"></script>
        <script type="text/javascript" src="./../js/script.js"></script>
             
    </body>
</html>
