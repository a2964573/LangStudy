import "Framework/afc/component/ANavigator.js";

/**
Constructor
Do not call Function in Constructor.
*/
class NaviTest01App()
{
	super();

	//TODO:edit here

}
extends AApplication;


function NaviTest01App*onReady()
{
	super.onReady();

	this.setMainContainer(new APage('main'));
	this.mainContainer.open('Source/MainView.lay');

	//TODO:edit here

	this.navi = new ANavigator();
	this.regiPage();
	
	this.navi.goPage("Page0001");
};

function NaviTest01App*unitTest(unitUrl)
{
	//TODO:edit here

	this.onReady();

	super.unitTest(unitUrl);
};

function NaviTest01App*regiPage()
{
	this.navi.registerPage("Source/Pages/Page0001.lay", "Page0001");
	this.navi.registerPage("Source/Pages/Page0002.lay", "Page0002");
	this.navi.registerPage("Source/Pages/Page0003.lay", "Page0003");
};