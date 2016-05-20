<?hh //strict
namespace Zumb\Dein;

use Zumb\Dein\ContainerService;
use Zumb\Dein\Providers\ContainerServiceProvider;
use Zumb\Dein\Providers\ProvidersProvider;

class Factory
{
  public static function create():ContainerService
  {
    $container = new ContainerService(new Instantiator());
    $container->addProvider(new ContainerServiceProvider($container));
    $container->addProvider(ProvidersProvider::class);
    return $container;
  }
}
