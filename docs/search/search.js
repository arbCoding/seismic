function convertToId(e){var n,s,t="";for(i=0;i<e.length;i++)n=e.charAt(i),s=n.charCodeAt(0),n.match(/[a-z0-9\u0080-\uFFFF]/)?t+=n:s<16?t+="_0"+s.toString(16):t+="_"+s.toString(16);return t}function getXPos(e){var t=0;if(e.offsetWidth)for(;e&&e!=document.body;)t+=e.offsetLeft,e=e.offsetParent;return t}function getYPos(e){var t=0;if(e.offsetWidth)for(;e&&e!=document.body;)t+=e.offsetTop,e=e.offsetParent;return t}var searchResults=new SearchResults("searchResults");function SearchBox(e,t,n){(!e||!t)&&alert("Missing parameters to SearchBox."),(!n||n=="")&&(n=".html"),this.name=e,this.resultsPath=t,this.keyTimeout=0,this.keyTimeoutLength=500,this.closeSelectionTimeout=300,this.lastSearchValue="",this.lastResultsPage="",this.hideTimeout=0,this.searchIndex=0,this.searchActive=!1,this.extension=n,this.DOMSearchField=function(){return document.getElementById("MSearchField")},this.DOMSearchSelect=function(){return document.getElementById("MSearchSelect")},this.DOMSearchSelectWindow=function(){return document.getElementById("MSearchSelectWindow")},this.DOMPopupSearchResults=function(){return document.getElementById("MSearchResults")},this.DOMPopupSearchResultsWindow=function(){return document.getElementById("MSearchResultsWindow")},this.DOMSearchClose=function(){return document.getElementById("MSearchClose")},this.DOMSearchBox=function(){return document.getElementById("MSearchBox")},this.OnSearchFieldFocus=function(e){this.Activate(e)},this.OnSearchSelectShow=function(){var e=this.DOMSearchSelectWindow(),t=this.DOMSearchSelect(),s=getXPos(t),n=getYPos(t);return n+=t.offsetHeight,e.style.display="block",e.style.left=s+"px",e.style.top=n+"px",this.hideTimeout&&(clearTimeout(this.hideTimeout),this.hideTimeout=0),!1},this.OnSearchSelectHide=function(){this.hideTimeout=setTimeout(this.CloseSelectionWindow.bind(this),this.closeSelectionTimeout)},this.OnSearchFieldChange=function(e){this.keyTimeout&&(clearTimeout(this.keyTimeout),this.keyTimeout=0);var n,s,o,a,t=e||window.event;if(t.keyCode==40||t.keyCode==13){if(t.shiftKey==1){this.OnSearchSelectShow(),n=this.DOMSearchSelectWindow();for(i=0;i<n.childNodes.length;i++)if(s=n.childNodes[i],s.className=="SelectItem"){s.focus();return}return}o=searchResults.NavNext(0),o&&o.focus()}else if(t.keyCode==27){t.stopPropagation(),this.DOMSearchField().blur(),this.DOMPopupSearchResultsWindow().style.display="none",this.DOMSearchClose().style.display="none",this.lastSearchValue="",this.Activate(!1);return}a=this.DOMSearchField().value.replace(/ +/g,""),a!=this.lastSearchValue&&(a!=""?this.keyTimeout=setTimeout(this.Search.bind(this),this.keyTimeoutLength):(this.DOMPopupSearchResultsWindow().style.display="none",this.DOMSearchClose().style.display="none",this.lastSearchValue=""))},this.SelectItemCount=function(){var s,t=0,n=this.DOMSearchSelectWindow();for(i=0;i<n.childNodes.length;i++)s=n.childNodes[i],s.className=="SelectItem"&&t++;return t},this.SelectItemSet=function(e){var t,n,s,o=0,i=this.DOMSearchSelectWindow();for(t=0;t<i.childNodes.length;t++)n=i.childNodes[t],n.className=="SelectItem"&&(s=n.firstChild,o==e?s.innerHTML="&#8226;":s.innerHTML="&#160;",o++)},this.OnSelectItem=function(e){this.searchIndex=e,this.SelectItemSet(e);var t=this.DOMSearchField().value.replace(/ +/g,"");t!=""&&this.searchActive&&this.Search()},this.OnSearchSelectKey=function(e){var t=e||window.event;return t.keyCode==40&&this.searchIndex<this.SelectItemCount()?(this.searchIndex++,this.OnSelectItem(this.searchIndex)):t.keyCode==38&&this.searchIndex>0?(this.searchIndex--,this.OnSelectItem(this.searchIndex)):(t.keyCode==13||t.keyCode==27)&&(t.stopPropagation(),this.OnSelectItem(this.searchIndex),this.CloseSelectionWindow(),this.DOMSearchField().focus()),!1},this.CloseResultsWindow=function(){this.DOMPopupSearchResultsWindow().style.display="none",this.DOMSearchClose().style.display="none",this.Activate(!1)},this.CloseSelectionWindow=function(){this.DOMSearchSelectWindow().style.display="none"},this.Search=function(){this.keyTimeout=0;var e,n,s,o,i,a,r,l,d,u,t=this.DOMSearchField().value.replace(/^ +/,""),h=t.toLowerCase().charCodeAt(0),c=t.substr(0,1).toLowerCase();55296<=h&&h<=56319&&t>1&&(c=t.substr(0,2)),n=indexSectionsWithContent[this.searchIndex].indexOf(c),n!=-1&&(r=n.toString(16),i=this.resultsPath+indexSectionNames[this.searchIndex]+"_"+r+".js"),a=function(e,t,n){var s=document.createElement("script");s.src=e,s.onload=t,s.onreadystatechange=t,n.appendChild(s)},e=this.DOMPopupSearchResultsWindow(),o=this.DOMSearchBox(),l=this.DOMPopupSearchResults(),d=this.DOMSearchClose(),u=this.resultsPath,s=function(){if(document.getElementById("Loading").style.display="none",typeof searchData!="undefined"&&(createResults(u),document.getElementById("NoMatches").style.display="none"),n!=-1?searchResults.Search(t):searchResults.Search("===="),e.style.display!="block"){d.style.display="inline-block";var i,a,c,h,s=getXPos(o)+150,r=getYPos(o)+20;e.style.display="block",s-=l.offsetWidth,c=document.body.clientWidth,h=document.body.clientHeight,i=300,s<10&&(s=10),i+s+8>c&&(i=c-s-8),a=400,a+r+8>h&&(a=h-r-8),e.style.top=r+"px",e.style.left=s+"px",e.style.width=i+"px",e.style.height=a+"px"}},i?a(i,s,this.DOMPopupSearchResultsWindow()):s(),this.lastSearchValue=t},this.Activate=function(e){e||this.DOMPopupSearchResultsWindow().style.display=="block"?(this.DOMSearchBox().className="MSearchBoxActive",this.searchActive=!0):e||(this.DOMSearchBox().className="MSearchBoxInactive",this.searchActive=!1,this.lastSearchValue="",this.lastResultsPage="",this.DOMSearchField().value="")}}function SearchResults(){this.lastMatchCount=0,this.lastKey=0,this.repeatOn=!1,this.FindChildElement=function(e){for(var n=document.getElementById(e),t=n.firstChild;t&&t!=n;){if(t.nodeName.toLowerCase()=="div"&&t.className=="SRChildren")return t;if(t.nodeName.toLowerCase()=="div"&&t.hasChildNodes())t=t.firstChild;else if(t.nextSibling)t=t.nextSibling;else{do t=t.parentNode;while(t&&t!=n&&!t.nextSibling)t&&t!=n&&(t=t.nextSibling)}}},this.Toggle=function(e){var t=this.FindChildElement(e);t&&(t.style.display=="block"?t.style.display="none":t.style.display="block")},this.Search=function(e){e||(e=window.location.search,e=e.substring(1),e=unescape(e)),e=e.replace(/^ +/,""),e=e.replace(/ +$/,""),e=e.toLowerCase(),e=convertToId(e);for(var t,n,i=document.getElementsByTagName("div"),s=0,o=0;o<i.length;)t=i.item(o),t.className=="SRResult"&&(n=t.id.toLowerCase(),n=n.replace(/^sr\d*_/,""),e.length<=n.length&&n.substr(0,e.length)==e?(t.style.display="block",s++):t.style.display="none"),o++;return document.getElementById("Searching").style.display="none",s==0?document.getElementById("NoMatches").style.display="block":document.getElementById("NoMatches").style.display="none",this.lastMatchCount=s,!0},this.NavNext=function(e){for(;1;){var t,n="Item"+e;if(t=document.getElementById(n),t&&t.parentNode.parentNode.style.display=="block")break;if(!t)break;t=null,e++}return t},this.NavPrev=function(e){for(;1;){var t,n="Item"+e;if(t=document.getElementById(n),t&&t.parentNode.parentNode.style.display=="block")break;if(!t)break;t=null,e--}return t},this.ProcessKeys=function(e){if(e.type=="keydown")this.repeatOn=!1,this.lastKey=e.keyCode;else if(e.type=="keypress"){if(!this.repeatOn)return this.lastKey&&(this.repeatOn=!0),!1}else e.type=="keyup"&&(this.lastKey=0,this.repeatOn=!1);return this.lastKey!=0},this.Nav=function(e,t){var n,s,o,i,r,c,l,a=e||window.event;if(a.keyCode==13)return!0;if(!this.ProcessKeys(a))return!1;if(this.lastKey==38){if(i=t-1,n=this.NavPrev(i),n&&(r=this.FindChildElement(n.parentNode.parentNode.id),r&&r.style.display=="block"))for(c=0;1;){if(l=document.getElementById("Item"+i+"_c"+c),l)n=l;else break;c++}n?n.focus():document.getElementById("MSearchField").focus()}else if(this.lastKey==40)i=t+1,o=document.getElementById("Item"+t),s=this.FindChildElement(o.parentNode.parentNode.id),s&&s.style.display=="block"&&(n=document.getElementById("Item"+t+"_c0")),n||(n=this.NavNext(i)),n&&n.focus();else if(this.lastKey==39)o=document.getElementById("Item"+t),s=this.FindChildElement(o.parentNode.parentNode.id),s&&(s.style.display="block");else if(this.lastKey==37)o=document.getElementById("Item"+t),s=this.FindChildElement(o.parentNode.parentNode.id),s&&(s.style.display="none");else if(this.lastKey==27)a.stopPropagation(),searchBox.CloseResultsWindow(),document.getElementById("MSearchField").focus();else if(this.lastKey==13)return!0;return!1},this.NavChild=function(e,t,n){var s,o,i=e||window.event;if(i.keyCode==13)return!0;if(!this.ProcessKeys(i))return!1;if(this.lastKey==38)n>0?(o=n-1,document.getElementById("Item"+t+"_c"+o).focus()):document.getElementById("Item"+t).focus();else if(this.lastKey==40)o=n+1,s=document.getElementById("Item"+t+"_c"+o),s||(s=this.NavNext(t+1)),s&&s.focus();else if(this.lastKey==27)i.stopPropagation(),searchBox.CloseResultsWindow(),document.getElementById("MSearchField").focus();else if(this.lastKey==13)return!0;return!1}}function setKeyActions(e,t){e.setAttribute("onkeydown",t),e.setAttribute("onkeypress",t),e.setAttribute("onkeyup",t)}function setClassAttr(e,t){e.setAttribute("class",t),e.setAttribute("className",t)}function createResults(e){var t,n,s,o,i,a,r,c,l,d=document.getElementById("SRResults");d.innerHTML="";for(t=0;t<searchData.length;t++){if(l=searchData[t][0],a=document.createElement("div"),a.setAttribute("id","SR_"+l),setClassAttr(a,"SRResult"),i=document.createElement("div"),setClassAttr(i,"SREntry"),n=document.createElement("a"),n.setAttribute("id","Item"+t),setKeyActions(n,"return searchResults.Nav(event,"+t+")"),setClassAttr(n,"SRSymbol"),n.innerHTML=searchData[t][1][0],i.appendChild(n),searchData[t][1].length==2)n.setAttribute("href",e+searchData[t][1][1][0]),n.setAttribute("onclick","searchBox.CloseResultsWindow()"),searchData[t][1][1][1]?n.setAttribute("target","_parent"):n.setAttribute("target","_blank"),r=document.createElement("span"),setClassAttr(r,"SRScope"),r.innerHTML=searchData[t][1][1][2],i.appendChild(r);else{n.setAttribute("href",'javascript:searchResults.Toggle("SR_'+l+'")'),c=document.createElement("div"),setClassAttr(c,"SRChildren");for(o=0;o<searchData[t][1].length-1;o++)s=document.createElement("a"),s.setAttribute("id","Item"+t+"_c"+o),setKeyActions(s,"return searchResults.NavChild(event,"+t+","+o+")"),setClassAttr(s,"SRScope"),s.setAttribute("href",e+searchData[t][1][o+1][0]),s.setAttribute("onclick","searchBox.CloseResultsWindow()"),searchData[t][1][o+1][1]?s.setAttribute("target","_parent"):s.setAttribute("target","_blank"),s.innerHTML=searchData[t][1][o+1][2],c.appendChild(s);i.appendChild(c)}a.appendChild(i),d.appendChild(a)}}function init_search(){var e,t,s,o,n=document.getElementById("MSearchSelectWindow");n.tabIndex=0;for(s in indexSectionLabels)e=document.createElement("a"),e.setAttribute("class","SelectItem"),e.setAttribute("onclick","searchBox.OnSelectItem("+s+")"),e.href="javascript:void(0)",e.innerHTML='<span class="SelectionMark">&#160;</span>'+indexSectionLabels[s],n.appendChild(e);searchBox.OnSelectItem(0),t=document.getElementById("MSearchSelect"),o=document.getElementById("MSearchSelectWindow"),t.tabIndex=0,t.addEventListener("keydown",function(e){(e.keyCode==13||e.keyCode==40)&&(e.preventDefault(),o.style.display=="block"?searchBox.CloseSelectionWindow():(searchBox.OnSearchSelectShow(),searchBox.DOMSearchSelectWindow().focus()))})}