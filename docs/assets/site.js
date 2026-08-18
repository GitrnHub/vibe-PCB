const year=document.querySelector('#year');
if(year) year.textContent=new Date().getFullYear();

const viewer=document.querySelector('#imageViewer');
const viewerImage=document.querySelector('#viewerImage');
const viewerTitle=document.querySelector('#viewerTitle');
const viewerClose=document.querySelector('#viewerClose');

for(const trigger of document.querySelectorAll('[data-lightbox]')){
  trigger.addEventListener('click',()=>{
    if(!viewer || !viewerImage) return;
    viewerImage.src=trigger.dataset.lightbox;
    viewerImage.alt=trigger.dataset.alt || 'Engineering view';
    if(viewerTitle) viewerTitle.textContent=trigger.dataset.alt || 'Engineering view';
    if(typeof viewer.showModal==='function') viewer.showModal();
  });
}

viewerClose?.addEventListener('click',()=>viewer?.close());
viewer?.addEventListener('click',(event)=>{
  const box=viewer.getBoundingClientRect();
  const outside=event.clientX<box.left||event.clientX>box.right||event.clientY<box.top||event.clientY>box.bottom;
  if(outside) viewer.close();
});
