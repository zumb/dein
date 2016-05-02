<?hh //strict
namespace Dein\Providers;

use Dein\Interfaces\Provider;
use Dein\ContainerService;
use Dein\Reflection\ClassInspector;

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
