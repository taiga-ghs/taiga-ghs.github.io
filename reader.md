# reader

<div id='the-input'>
 <label for="input-file">文本文件：</label><br>
 <input type="file" id="input-file">
</div>

<div id="content-target"></div>
<script type="text/javascript">
document.getElementById('input-file')
  .addEventListener('change', getFile)

function getFile(event) {
	const input = event.target
  if ('files' in input && input.files.length > 0) {
	  placeFileContent(
      document.getElementById('content-target'),
      input.files[0])
       document.getElementById('the-input').remove()
  }
}

function placeFileContent(target, file) {
	readFileContent(file).then(content => {
  	target.innerHTML = ("<p>"+content).replace(/\r?\n|\r/g, "</p><p>").replace(/\s{4}/g, "　　　　")+"</p>"
  }).catch(error => console.log(error))
}

function readFileContent(file) {
	const reader = new FileReader()
  return new Promise((resolve, reject) => {
    reader.onload = event => resolve(event.target.result)
    reader.onerror = error => reject(error)
    reader.readAsText(file)
  })
}
</script>