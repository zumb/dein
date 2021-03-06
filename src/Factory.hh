<?hh //strict
namespace Zumb\Dein;

use Zumb\Dein\ContainerService;
use Zumb\Dein\Providers\SingletonProvider;

class Factory
{
  public static function create():ContainerService
  {
    $instantiator = new Instantiator();
    $container = new ContainerService(
      $instantiator, new Resolver(), new ProvidersPool($instantiator)
    );
    $container->providers->add(new SingletonProvider($container), ContainerService::class);
    return $container;
  }
}
