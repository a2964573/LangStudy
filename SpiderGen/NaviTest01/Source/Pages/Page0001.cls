
/**
Constructor
Do not call Function in Constructor.
*/
class Page0001()
{
	super();

	//TODO:edit here

}
extends AView;


function Page0001*init(context, evtListener)
{
	super.init(context, evtListener);

	//TODO:edit here

};

function Page0001*onInitDone()
{
	super.onInitDone();

	//TODO:edit here

};

function Page0001*onActiveDone(isFirst)
{
	super.onActiveDone(isFirst);

	//TODO:edit here

};

function Page0001*onGoBtnClick(comp, info, e)
{
	var pageNum = comp.compId.slice(-1);
	
	theApp.navi.goPage("Page000"+pageNum, {});
};
