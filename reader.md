<h1 id='ttl'>阅读器v0.0.2.14</h1>

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
nem = new String
debug_content = new String

function topFunction() {
  document.body.scrollTop = 0; // For Safari
  document.documentElement.scrollTop = 0; // For Chrome, Firefox, IE and Opera
}

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
	debug_content = content
	ctt = content.slice(36)
	for (i=0;i<ctt.length;i++) {
		if (ctt[i] == '>') {
			name = ctt.slice(0,i)
			ctt = ctt.slice(i+1, -77).trim()
			break
		}
	}
	ctt = separateChapters(ctt)
	chp = ctt
	title = getTitle(ctt)
	ttl = title
	placeTOC(target)
  }).catch(error => console.log(error))
}

function placeTOC(target){
  	ttt.innerHTML="目录 - "+name
  	target.innerHTML = ""
  	for (i in chp) {
  		target.innerHTML += "<p onclick='placeChapter(document.getElementById(\"content-target\"),"+i+")'><a>"+ttl[i]+"</a></p>"
  	}
  	target.innerHTML += "<hr><p onclick=\"window.window.window['window'].location = window['window'].window['window']['window']['window']['window']['window']['window']['location']\"><a>换一本书</a></p>"
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
	target.innerHTML = "<p onclick='placeTOC(document.getElementById(\"content-target\"))'><a>返回目录</a></p>"
	target.innerHTML += content
	target.innerHTML += (chp_n>0?"<p onclick='placeChapter(document.getElementById(\"content-target\"),"+(chp_n-1)+");topFunction()'><a>前一章</a></p>":"")
	target.innerHTML += (chp_n+1<chp.length?"<p onclick='placeChapter(document.getElementById(\"content-target\"),"+(chp_n+1)+");topFunction()'><a>后一章</a></p>":"")
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