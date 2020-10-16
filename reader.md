<h1>阅读器</h1>

<div id='the-input'>
 <label for="input-file">文本文件：</label><br>
 <input type="file" id="input-file">
</div>

<div id="content-target"></div>
<script type="text/javascript">
document.getElementById('input-file')
  .addEventListener('change', getFile)

chp = new Array
ttl = new Array

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
	content = content.slice(35)
	for (i in content) {
		if (content[i] == '>') {
			name = content.slice(1,i)
			content = content.slice(i-1).trim()
			break
		}
	}
	content = separateChapters(content)
	chp = content
	title = getTitle(content)
	ttl = title
  	target.innerHTML = ""
  	for (i in content) {
  		target.innerHTML += "<p onclick='placeChapter(document.getElementById('content-target'),"+i+")'>"+ttl[i]+"</p>"
  	}
  }).catch(error => console.log(error))
}

sep_reg = /\n(?!\s{4})(?=.)/
function separateChapters(original) {
	results = new Array
	original = original.split(sep_reg)
	for (i of original){
		results.push(i.trim())
	}
	return results
}

function getTitle(chapters) {
	results = new Array
	for (i of chapters) {
		results.push(i.split("\n")[0].trim())
	}
	return results
}

function placeChapter(target, chp_n) {
	content = chp[chp_n]
	content = ("<p>"+content).replace(/\r?\n|\r/g, "</p><p>").replace(/\s{4}/g, "　　")+"</p>"
	target.innerHTML = content
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