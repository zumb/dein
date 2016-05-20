<?hh //partial

namespace spec\Dein\Providers;

use PhpSpec\ObjectBehavior;
use Prophecy\Argument;
use Dein\ContainerService;
use Dein\Reflection\ClassInspector;
use Dein\Interfaces\Provider;

class ProvidersProviderSpec extends ObjectBehavior
{
  public function let($container, $class, $provider)
  {
    $container->beADoubleOf(ContainerService::class);
    $class->beADoubleOf(ClassInspector::class);
    $provider->beADoubleOf(Provider::class);
    $this->beConstructedWith($container);
  }

  public function it_stores_providers_instances($container, $class, $provider)
  {
    $class->getName()
      ->willReturn("ProviderClass");
    $container->get("ProviderClass")
      ->willReturn($provider);
    $this->get($class)
      ->shouldReturn($provider);
    $this->get($class)
      ->shouldReturn($provider);
    $container->get("ProviderClass")
      ->shouldHaveBeenCalledTimes(1);
  }
}
