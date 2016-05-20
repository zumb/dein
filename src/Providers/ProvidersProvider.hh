<?hh //strict
namespace Zumb\Dein\Providers;

use Zumb\Dein\Interfaces\Provider;
use Zumb\Dein\Reflection\ClassInspector;
use Zumb\Dein\ContainerService;

class ProvidersProvider implements Provider<Provider<mixed>>
{
  protected Map<string, Provider<mixed>> $providers = Map{};

  public function __construct(
    protected ContainerService $container
  ){}

  public function get(ClassInspector<Provider<mixed>> $providerClass):Provider<mixed>
  {
    $provider = $this->providers->get($providerClass->getName());
    if($provider == null) {
      $provider = $this->container->get($providerClass->getName());
      invariant($provider instanceof Provider, "Not a provider");
      $this->providers->set($providerClass->getName(), $provider);
    }
    return $provider;
  }

}
