<h1 id='ttl'>阅读器</h1>

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
ttt = document.getElementById('ttl')

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
	content = content.slice(36)
	for (i in content) {
		if (content[i] == '>') {
			name = content.slice(0,i)
			content = content.slice(Number(i)+1, -76).trim()
			break
		}
	}
	content = separateChapters(content)
	chp = content
	title = getTitle(content)
	ttl = title
  	target.innerHTML = ""
  	for (i in content) {
  		target.innerHTML += "<p onclick='placeChapter(document.getElementById(\"content-target\"),"+i+")'><a>"+ttl[i]+"</a></p>"
  	}
  	ttt.innerHTML="选择章节"
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
	ttt.innerHTML=ttl[chp_n]
	content = chp[chp_n]
	content = ("<p>"+content).replace(/\r?\n|\r/g, "</p><p>").replace(/\s{4}/g, "　　")+"</p>"
	target.innerHTML = content
	target.innerHTML += "<ponclick='placeChapter(document.getElementById(\"content-target\"),"+(chp_n-1)+")'><a>前一章</a></p><p onclick='placeChapter(document.getElementById(\"content-target\"),"+(chp_n+1)+")'><a>后一章</a></p>"
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