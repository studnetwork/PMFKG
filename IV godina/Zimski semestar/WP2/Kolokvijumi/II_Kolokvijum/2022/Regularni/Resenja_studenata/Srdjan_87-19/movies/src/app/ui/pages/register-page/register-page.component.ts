import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from 'src/app/core/services/auth.service';

@Component({
  selector: 'app-register-page',
  templateUrl: './register-page.component.html'
})
export class RegisterPageComponent {
  
  email: string = '';
  name: string = '';
  password: string = '';

  constructor(
    private router: Router,
    private authService: AuthService
  ) {}

  register() {
    this.authService.register(this.email, this.name, this.password).subscribe(jwt => {
      this.authService.saveJwt(jwt);

      this.router.navigateByUrl('/');
    })
  }
}
