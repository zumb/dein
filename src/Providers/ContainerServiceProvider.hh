<?hh //strict
namespace Zumb\Dein\Providers;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\ContainerService;
use Zumb\Dein\Reflection\ClassInspector;

class ContainerServiceProvider implements Provider<ContainerService>
{
  public function __construct(
    protected ContainerService $container
  ) {}

  public function get(ClassInspector<ContainerService> $class):ContainerService
  {
    return $this->container;
  }
}
