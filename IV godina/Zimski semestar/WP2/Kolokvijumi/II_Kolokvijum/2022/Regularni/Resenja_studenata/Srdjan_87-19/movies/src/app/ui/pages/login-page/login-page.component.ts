import { Component } from '@angular/core';
import { Router } from '@angular/router';
import { AuthService } from 'src/app/core/services/auth.service';

@Component({
  selector: 'app-login-page',
  templateUrl: './login-page.component.html'
})
export class LoginPageComponent {

  email: string = '';
  password: string = '';

  constructor(
    private router: Router,
    private authService: AuthService
  ) {}

  login() {
    this.authService.login(this.email, this.password).subscribe(jwt => {
      this.authService.saveJwt(jwt);

      this.router.navigateByUrl('/');
    })
  }
}
